:: Update godot-cpp submodule (https://stackoverflow.com/a/5828561)
call set godot_cpp_branch=4.4
call cd godot-cpp
call git fetch
call git checkout %godot_cpp_branch%
call git pull origin %godot_cpp_branch%
pause