:: Prevent quit on error
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit

:: Update submodules
git submodule update --remote --merge