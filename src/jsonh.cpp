#include <godot_cpp/core/class_db.hpp>

#include "jsonh.hpp"
#include "jsonh-org/jsonh_cpp_amalgamated.hpp"

using namespace godot;
using namespace nlohmann;
using namespace jsonh_cpp;
using namespace jsonh_gdextension;

Jsonh *Jsonh::singleton = nullptr;

void Jsonh::_bind_methods() {
	ClassDB::bind_method(D_METHOD("parse_element", "string"), &Jsonh::parse_element);
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

Dictionary Jsonh::parse_element(const String& string) noexcept {
	std::stack<Variant> current_nodes;
	std::optional<String> current_property_name;

	auto submit_node = [&](Variant node) {
		// Root value
		if (current_nodes.empty()) {
			return true;
		}
		// Array item
		if (!current_property_name) {
			((Array)current_nodes.top()).push_back(node);
			return false;
		}
		// Object property
		else {
			((Dictionary)current_nodes.top())[current_property_name.value()] = node;
			current_property_name.reset();
			return false;
		}
	};
	auto start_node = [&](Variant node) {
		submit_node(node);
		current_nodes.push(node);
	};

	for (const nonstd::expected<jsonh_token, std::string>& token_result : jsonh_reader(string.utf8().get_data()).read_element()) {
		// Check error
		if (!token_result) {
			return create_error_result(token_result.error().data());
		}
		jsonh_token token = token_result.value();

		switch (token.json_type) {
			// Null
			case json_token_type::null: {
				Variant node = Variant(nullptr);
				if (submit_node(node)) {
					return create_value_result(node);
				}
				break;
			}
			// True
			case json_token_type::true_bool: {
				Variant node = Variant(true);
				if (submit_node(node)) {
					return create_value_result(node);
				}
				break;
			}
			// False
			case json_token_type::false_bool: {
				Variant node = Variant(false);
				if (submit_node(node)) {
					return create_value_result(node);
				}
				break;
			}
			// String
			case json_token_type::string: {
				Variant node = Variant(token.value.data());
				if (submit_node(node)) {
					return create_value_result(node);
				}
				break;
			}
			// Number
			case json_token_type::number: {
				nonstd::expected<long double, std::string> result = jsonh_number_parser::parse(token.value);
				if (!result) {
					return create_error_result(result.error().data());
				}
				Variant node = Variant((double)result.value());
				if (submit_node(node)) {
					return create_value_result(node);
				}
				break;
			}
			// Start Object
			case json_token_type::start_object: {
				Variant node = Dictionary();
				start_node(node);
				break;
			}
			// Start Array
			case json_token_type::start_array: {
				Variant node = Array();
				start_node(node);
				break;
			}
			// End Object/Array
			case json_token_type::end_object: case json_token_type::end_array: {
				// Nested node
				if (current_nodes.size() > 1) {
					current_nodes.pop();
				}
				// Root node
				else {
					return create_value_result(current_nodes.top());
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
				return create_error_result("Token type not implemented");
			}
		}
	}

	// End of input
	return create_error_result("Expected token, got end of input");
}

Dictionary Jsonh::create_value_result(const Variant& value) noexcept {
	Dictionary result = {};
	result["value"] = value;
	return result;
}
Dictionary Jsonh::create_error_result(const String& error) noexcept {
	Dictionary result = {};
	result["error"] = error;
	return result;
}