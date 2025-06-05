:: Prevent quit on error
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit

:: Update godot-cpp submodule (https://stackoverflow.com/a/5828561)
cd godot-cpp
git fetch
git checkout 4.4
git pull origin 4.4