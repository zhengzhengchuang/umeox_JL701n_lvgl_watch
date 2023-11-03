@echo off
setlocal enabledelayedexpansion

del output.txt output_modified.txt

cd ../sdk/

for %%I in ("%~dp0") do set "sourePath=%%~fI"
echo %sourePath%

for %%I in (../sdk/) do set "currentPath=%%~fI"
echo %currentPath%

set "folder=apps/common/ui/lvgl"
set "outputFile=%sourePath%/output.txt"

if not exist "%folder%" (
    echo Folder does not exist.
	pause
    exit /b
)

echo Listing .c files in %folder% and its subfolders...

for /r "%folder%" %%F in (*.c) do (
    set "relativePath=%%F"
    @rem set "relativePath=!relativePath:%currentPath%\=!"
    echo !relativePath! >> %outputFile%
)

echo Done. Output saved to %outputFile%.

set "input=%sourePath%/output.txt"
set "output=%sourePath%/output_modified.txt"

for /f "delims=" %%a in ('type "%input%"') do (
    set "line=%%a"
	set "line=!line:%currentPath%=    !"
    set "line=!line:\=/!"
    
    echo !line! \>>"%output%"
	
)

echo "hhhhhhh"

cd %sourePath%
del output.txt



cd ../sdk/
set "houtputFile=%sourePath%/h.txt"

for /r "%folder%" /d %%i in (*) do (
    echo %%~nxi >> "%houtputFile%"
)

echo "File listing complete."



endlocal

pause