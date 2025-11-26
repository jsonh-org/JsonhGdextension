#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/label.hpp>

#include "jsonh_result.hpp"

using namespace godot;

namespace jsonh_gdextension {

class JsonhResult : public RefCounted {
	GDCLASS(JsonhResult, RefCounted);

public:
	static Ref<JsonhResult> from_value(const Variant &value = Variant()) noexcept;
	static Ref<JsonhResult> from_error(const String &error) noexcept;

	const Variant &get_value() const noexcept;
	const String &get_error() const noexcept;
	bool get_is_error() const noexcept;
	bool get_is_value() const noexcept;

protected:
	static void _bind_methods();

private:
	Variant value = Variant();
	String error = String();
	bool is_error = false;

	JsonhResult() noexcept;
	JsonhResult(const Variant &value, const String &error, bool is_error) noexcept;
};

}