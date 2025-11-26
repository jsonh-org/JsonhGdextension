#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/label.hpp>

#include "jsonh-org/jsonh_cpp_amalgamated.hpp"

using namespace godot;
using namespace jsonh_cpp;

namespace jsonh_gdextension {

class JsonhOptions : public Resource {
	GDCLASS(JsonhOptions, Resource);

public:
	jsonh_reader_options reader_options = jsonh_reader_options();

	JsonhOptions() noexcept;
	JsonhOptions(jsonh_reader_options options) noexcept;

	jsonh_version get_version() noexcept;
	void set_version(jsonh_version version) noexcept;
	JsonhOptions with_version(jsonh_version version) const noexcept;

	bool get_incomplete_inputs() noexcept;
	void set_incomplete_inputs(bool incomplete_inputs) noexcept;
	JsonhOptions with_incomplete_inputs(bool incomplete_inputs) const noexcept;

	bool get_parse_single_element() noexcept;
	void set_parse_single_element(bool parse_single_element) noexcept;
	JsonhOptions with_parse_single_element(bool parse_single_element) const noexcept;

protected:
	static void _bind_methods();
};
}