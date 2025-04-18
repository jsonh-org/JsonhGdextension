:: Prevent quit on error
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit

:: Dump extension_api.json
set godot="C:/Users/patri/Documents/Programs/Godot_v4.4.1-stable_mono_win64/Godot_v4.4.1-stable_mono_win64.exe"
%godot% --dump-extension-api