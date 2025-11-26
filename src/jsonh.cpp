#include <godot_cpp/core/class_db.hpp>

#include "jsonh.hpp"

using namespace godot;
using namespace nlohmann;
using namespace jsonh_cpp;
using namespace jsonh_gdextension;

Jsonh *Jsonh::singleton = nullptr;

void Jsonh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("parse_element", "string", "options"), &Jsonh::parse_element, DEFVAL(Dictionary()));
}

Jsonh *Jsonh::get_singleton() {
	return singleton;
}

Jsonh::Jsonh() {
	ERR_FAIL_COND(singleton != nullptr);
	singleton = this;
}

Jsonh::~Jsonh() {
	ERR_FAIL_COND(singleton != this);
	singleton = nullptr;
}

Ref<JsonhResult> Jsonh::parse_element(const String &string, const JsonhOptions &options) noexcept {
	jsonh_reader reader(string.utf8().get_data(), options.reader_options);

	std::stack<Variant> current_elements;
	std::optional<String> current_property_name;

	auto submit_element = [&](const Variant &element) -> bool {
		// Root value
		if (current_elements.empty()) {
			return true;
		}
		// Array item
		if (!current_property_name) {
			((Array)current_elements.top()).push_back(element);
			return false;
		}
		// Object property
		else {
			((Dictionary)current_elements.top())[current_property_name.value()] = element;
			current_property_name.reset();
			return false;
		}
	};
	auto start_element = [&](const Variant &element) -> void {
		submit_element(element);
		current_elements.push(element);
	};
	auto parse_next_element = [&]() -> Ref<JsonhResult> {
		for (const nonstd::expected<jsonh_token, std::string> &token_result : reader.read_element()) {
			// Check error
			if (!token_result) {
				return JsonhResult::from_error(token_result.error().data());
			}
			jsonh_token token = token_result.value();

			switch (token.json_type) {
				// Null
				case json_token_type::null: {
					Variant element = Variant(nullptr);
					if (submit_element(element)) {
						return JsonhResult::from_value(element);
					}
					break;
				}
				// True
				case json_token_type::true_bool: {
					Variant element = Variant(true);
					if (submit_element(element)) {
						return JsonhResult::from_value(element);
					}
					break;
				}
				// False
				case json_token_type::false_bool: {
					Variant element = Variant(false);
					if (submit_element(element)) {
						return JsonhResult::from_value(element);
					}
					break;
				}
				// String
				case json_token_type::string: {
					Variant element = Variant(token.value.data());
					if (submit_element(element)) {
						return JsonhResult::from_value(element);
					}
					break;
				}
				// Number
				case json_token_type::number: {
					nonstd::expected<long double, std::string> result = jsonh_number_parser::parse(token.value);
					if (!result) {
						return JsonhResult::from_error(result.error().data());
					}
					Variant element = Variant((double)result.value());
					if (submit_element(element)) {
						return JsonhResult::from_value(element);
					}
					break;
				}
				// Start Object
				case json_token_type::start_object: {
					Variant element = Dictionary();
					start_element(element);
					break;
				}
				// Start Array
				case json_token_type::start_array: {
					Variant element = Array();
					start_element(element);
					break;
				}
				// End Object/Array
				case json_token_type::end_object:
				case json_token_type::end_array: {
					// Nested element
					if (current_elements.size() > 1) {
						current_elements.pop();
					}
					// Root element
					else {
						return JsonhResult::from_value(current_elements.top());
					}
					break;
				}
				// Property Name
				case json_token_type::property_name: {
					current_property_name = token.value.data();
					break;
				}
				// Comment
				case json_token_type::comment: {
					break;
				}
				// Not implemented
				default: {
					return JsonhResult::from_error("Token type not implemented");
				}
			}
		}

		// End of input
		return JsonhResult::from_error("Expected token, got end of input");
	};

	// Parse next element
	Ref<JsonhResult> next_element = parse_next_element();

	// Ensure exactly one element
	if (reader.options.parse_single_element) {
		for (const nonstd::expected<jsonh_token, std::string> &token : reader.read_end_of_elements()) {
			if (!token) {
				return JsonhResult::from_error(token.error().data());
			}
		}
	}

	return next_element;
}