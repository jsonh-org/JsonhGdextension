#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

namespace jsonh_gdextension {

class Jsonh : public Object {
	GDCLASS(Jsonh, Object);

public:
	static Jsonh *get_singleton();

	Jsonh();
	~Jsonh();

	Dictionary parse_element(const String& string) noexcept;

protected:
	static void _bind_methods();

private:
	static Jsonh *singleton;

	static Dictionary create_value_result(const Variant& value) noexcept;
	static Dictionary create_error_result(const String& error) noexcept;
};

}