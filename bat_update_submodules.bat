:: Prevent quit on error
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit

:: Update submodules (https://stackoverflow.com/a/5828561)
cd godot-cpp
git fetch
git checkout master
git pull origin master