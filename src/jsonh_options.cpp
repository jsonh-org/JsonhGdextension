#include <godot_cpp/core/class_db.hpp>

#include "jsonh_options.hpp"

using namespace godot;
using namespace jsonh_gdextension;

void JsonhOptions::_bind_methods() {
}

JsonhOptions::JsonhOptions() noexcept {
}

JsonhOptions::JsonhOptions(jsonh_cpp::jsonh_reader_options options) noexcept {
	this->options = options;
}