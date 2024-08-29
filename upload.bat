@ECHO ON

set BASEDIR=%~dp0
PUSHD %BASEDIR%

REM Remove-Item -Recurse -Force build
RMDIR /Q /S build

conan create . -c tools.build:skip_test=true --build=missing

@echo off

for /f "tokens=3" %%i in ('find "version" %~dp0/conanfile.py') do  set version=%%i
    set version=%version:~1,-1%

for /f "tokens=3" %%i in ('find "name = " %~dp0/conanfile.py') do  set name=%%i
    set name=%name:~1,-1%
	
echo %version%
echo %name%

@echo off

REM Get the list of available remotes
for /f "tokens=1 delims=:" %%a in ('conan remote list') do (
    if not "%%a" == "conancenter" (
		echo Uploading to remote: %%a
        conan upload "%name%/%version%" -r="%%a"
		conan search "%name%/%version%" -r="%%a"
		if errorlevel 1 (
			echo Error uploading to remote '%%a'
		)
    )
)

echo Done
