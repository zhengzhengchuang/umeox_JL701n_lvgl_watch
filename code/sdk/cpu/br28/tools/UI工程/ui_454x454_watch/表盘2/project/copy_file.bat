@echo off

setlocal enabledelayedexpansion
..\..\..\UITools\style_table -stylefile project.bin -prj 0x1
copy .\project.bin ..\..\..\..\ui_resource\watch2.sty
copy .\result.bin  ..\..\..\..\ui_resource\watch2.res
copy .\result.str  ..\..\..\..\ui_resource\watch2.str
copy .\version.txt  ..\..\..\..\ui_resource\watch2.json
..\..\..\UITools\redefined -infile ename.h -prefix watch2 -outfile rename.h
if exist "..\..\..\..\..\..\..\apps\watch\include\ui\" (
	..\..\..\UITools\FileCompare.exe .\rename.h
	if !errorlevel! neq 1 (
    	copy .\rename.h     ..\..\..\..\..\..\..\apps\watch\include\ui\style_watch2.h
	)
)

call ..\..\..\UITools\sdk_compile.bat
exit
