call "%VS120COMNTOOLS%vsvars32.bat"
cd ..
msbuild CppScript.sln /m /p:Configuration=Release;Platform=Win32
pause
