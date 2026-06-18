:: Prevent quit on error
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit

:: Update godot-cpp submodule (https://stackoverflow.com/a/5828561)
set godot_cpp_branch=4.4
cd godot-cpp
git fetch
git checkout %godot_cpp_branch%
git pull origin %godot_cpp_branch%