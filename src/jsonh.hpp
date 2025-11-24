#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/label.hpp>

#include "jsonh-org/jsonh_cpp_amalgamated.hpp"
#include "jsonh_result.hpp"

using namespace godot;

namespace jsonh_gdextension {

class Jsonh : public Object {
	GDCLASS(Jsonh, Object);

public:
	static Jsonh *get_singleton();

	Jsonh();
	~Jsonh();

	Ref<JsonhResult> parse_element(const String &string, const Dictionary &options = {}) noexcept;

protected:
	static void _bind_methods();

private:
	static Jsonh *singleton;
};

}