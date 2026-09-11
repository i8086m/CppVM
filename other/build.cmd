rmdir /s /q __pycache__
python -m compileall asm.py
rename "%~dp0__pycache__\asm.cpython-36.pyc" "asm.pyc"
del "%~dp0__pycache__\asm.cpython-36.pyc"

for /f "delims=" %%A in ('cd') do (
     set foldername=%%~nxA
    )
set foldername=%foldername%_build
rmdir /s /q %foldername%
	
rename "__pycache__" "%foldername%"

copy "Assemble & Run.cmd" "%~dp0%foldername%\Assemble & Run.cmd"
copy "Assemble.cmd" "%~dp0%foldername%\Assemble.cmd"
copy "CppVM.exe" "%~dp0%foldername%\CppVM.exe"
copy "readme.txt" "%~dp0%foldername%\readme.txt"
xcopy "examples" "%~dp0%foldername%\examples" /s/h/e/k/f/c/i
xcopy "modules" "%~dp0%foldername%\modules" /s/h/e/k/f/c/i
pause