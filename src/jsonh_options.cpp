#include <godot_cpp/core/class_db.hpp>

#include "jsonh_options.hpp"

using namespace godot;
using namespace jsonh_gdextension;

void JsonhOptions::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_version"), &JsonhOptions::get_version);
	ClassDB::bind_method(D_METHOD("set_version", "version"), &JsonhOptions::set_version);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "version"), "set_version", "get_version");

	ClassDB::bind_method(D_METHOD("with_version", "version"), &JsonhOptions::with_version);

	ClassDB::bind_method(D_METHOD("get_incomplete_inputs"), &JsonhOptions::get_incomplete_inputs);
	ClassDB::bind_method(D_METHOD("set_incomplete_inputs", "incomplete_inputs"), &JsonhOptions::set_incomplete_inputs);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "incomplete_inputs"), "set_incomplete_inputs", "get_incomplete_inputs");

	ClassDB::bind_method(D_METHOD("with_incomplete_inputs", "incomplete_inputs"), &JsonhOptions::with_incomplete_inputs);

	ClassDB::bind_method(D_METHOD("get_parse_single_element"), &JsonhOptions::get_parse_single_element);
	ClassDB::bind_method(D_METHOD("set_parse_single_element", "parse_single_element"), &JsonhOptions::set_parse_single_element);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "parse_single_element"), "set_parse_single_element", "get_parse_single_element");

	ClassDB::bind_method(D_METHOD("with_parse_single_element", "parse_single_element"), &JsonhOptions::with_parse_single_element);
}

JsonhOptions::JsonhOptions() noexcept {
}

JsonhOptions::JsonhOptions(jsonh_cpp::jsonh_reader_options reader_options) noexcept {
	this->reader_options = reader_options;
}

jsonh_version JsonhOptions::get_version() noexcept {
	return reader_options.version;
}

void JsonhOptions::set_version(jsonh_version version) noexcept {
	reader_options.version = version;
}

JsonhOptions JsonhOptions::with_version(jsonh_version version) const noexcept {
	JsonhOptions new_options(*this);
	new_options.reader_options.version = version;
	return new_options;
}

bool JsonhOptions::get_incomplete_inputs() noexcept {
	return reader_options.incomplete_inputs;
}

void JsonhOptions::set_incomplete_inputs(bool incomplete_inputs) noexcept {
	reader_options.incomplete_inputs = incomplete_inputs;
}

JsonhOptions JsonhOptions::with_incomplete_inputs(bool incomplete_inputs) const noexcept {
	JsonhOptions new_options(*this);
	new_options.reader_options.incomplete_inputs = incomplete_inputs;
	return new_options;
}

bool JsonhOptions::get_parse_single_element() noexcept {
	return reader_options.parse_single_element;
}

void JsonhOptions::set_parse_single_element(bool parse_single_element) noexcept {
	reader_options.parse_single_element = parse_single_element;
}

JsonhOptions JsonhOptions::with_parse_single_element(bool parse_single_element) const noexcept {
	JsonhOptions new_options(*this);
	new_options.reader_options.parse_single_element = parse_single_element;
	return new_options;
}