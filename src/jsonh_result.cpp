#include <godot_cpp/core/class_db.hpp>

#include "jsonh_result.hpp"

using namespace godot;
using namespace jsonh_gdextension;

void JsonhResult::_bind_methods() {
	ClassDB::bind_static_method("JsonhResult", D_METHOD("from_value", "value"), &JsonhResult::from_value);
	ClassDB::bind_static_method("JsonhResult", D_METHOD("from_error", "error"), &JsonhResult::from_error);

	ClassDB::bind_method(D_METHOD("get_value"), &JsonhResult::get_value);
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "value"), StringName(), "get_value");

	ClassDB::bind_method(D_METHOD("get_error"), &JsonhResult::get_error);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "error"), StringName(), "get_error");

	ClassDB::bind_method(D_METHOD("is_error"), &JsonhResult::get_is_error);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_error"), StringName(), "get_is_error");

	ClassDB::bind_method(D_METHOD("is_value"), &JsonhResult::get_is_value);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_value"), StringName(), "get_is_value");
}

JsonhResult::JsonhResult() noexcept {
}

JsonhResult::JsonhResult(const Variant &value, const String &error, bool is_error) noexcept {
	this->value = value;
	this->error = error;
	this->is_error = is_error;
}

Ref<JsonhResult> JsonhResult::from_value(const Variant &value) noexcept {
	return Ref<JsonhResult>(memnew(JsonhResult(value, String(), false)));
}

Ref<JsonhResult> JsonhResult::from_error(const String &error) noexcept {
	return Ref<JsonhResult>(memnew(JsonhResult(Variant(), error, true)));
}

const Variant &JsonhResult::get_value() noexcept {
	if (is_error) {
		UtilityFunctions::push_error("Result was error");
	}
	return value;
}

const String &JsonhResult::get_error() noexcept {
	if (!is_error) {
		UtilityFunctions::push_error("Result was value");
	}
	return error;
}

bool JsonhResult::get_is_error() noexcept {
	return is_error;
}

bool JsonhResult::get_is_value() noexcept {
	return !is_error;
}