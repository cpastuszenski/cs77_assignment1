@echo off

echo "test01: Ray-Sphere intersection"
trace.exe -s 1 scenes/test01.json || goto :error

echo "test02: Ray-Triangle intersection"
trace.exe -s 1 scenes/test02.json || goto :error

echo "test03: Shadow test"
trace.exe -s 1 scenes/test03.json || goto :error

echo "test04: Reflection"
trace.exe -s 1 scenes/test04.json || goto :error

echo "test05: Supersample"
trace.exe -s 9 scenes/test05.json || goto :error

echo "test06: Large scene"
trace.exe -s 9 -m 1 scenes/test06.json


echo "All completed successfully!"
goto :EOF

:error
echo "An error occurred!"
exit /b %errorlevel%
