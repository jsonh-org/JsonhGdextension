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

	static Ref<JsonhOptions> create() noexcept;

	int get_version() const noexcept;
	void set_version(int version) noexcept;
	Ref<JsonhOptions> with_version(int version) const noexcept;

	bool get_incomplete_inputs() const noexcept;
	void set_incomplete_inputs(bool incomplete_inputs) noexcept;
	Ref<JsonhOptions> with_incomplete_inputs(bool incomplete_inputs) const noexcept;

	bool get_parse_single_element() const noexcept;
	void set_parse_single_element(bool parse_single_element) noexcept;
	Ref<JsonhOptions> with_parse_single_element(bool parse_single_element) const noexcept;

protected:
	static void _bind_methods();

private:
	JsonhOptions() noexcept;
	JsonhOptions(jsonh_reader_options options) noexcept;
};

}