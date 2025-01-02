@echo off
@echo off

REM set CVTOOL="pyqt5"
REM set CVTOOL="pyside2"
REM set CVTOOL="pyside6"
set CVTOOL="pyside6"

if %CVTOOL% == "pyside2" goto pyside2_env
if %CVTOOL% == "pyside6" goto pyside6_env
:pyqt5_env
@SET ui2py=pyuic5
@SET ui2py_para=-x
@SET rcc=pyrcc5
goto next

:pyside2_env
@SET ui2py=pyside2-uic.exe
@SET ui2py_para=
@SET rcc=pyside2-rcc.exe
goto next

:pyside6_env
@SET ui2py=pyside6-uic.exe
@SET ui2py_para=
@SET rcc=pyside6-rcc.exe

:next

set nowYear=%date:~0,4%
set nowMonth=%date:~5,2%
set nowDay=%date:~8,2%
set nowHr=%time:~0,2%
rem 若時小於10，前面補0 例: 9→09, 8→08  
if %nowHr% LSS 10 set nowHr=0%nowHr%
set nowMin=%time:~3,2%
set nowSec=%time:~6,2%

SET curTime=%nowYear%%nowMonth%%nowDay%%nowHr%%nowMin%%nowSec%
IF NOT EXIST uibk mkdir uibk
echo copy "MainForm.ui" to "uibk\MainForm.ui.bk_%curTime%"
copy /Y MainForm.ui "uibk\MainForm.ui.bk_%curTime%"
echo delete "Ui_MainForm.py"
del /F/Q Ui_MainForm.py
echo gen Ui_MainForm.py
%ui2py% -o Ui_MainForm.py 	%ui2py_para%  resources/ui/MainForm.ui
%ui2py% -o Ui_Progres.py 	%ui2py_para%  resources/ui/Progress.ui

%rcc%	resources/Image.qrc -o Image_rc.py
echo copy /Y resources/ui/Progress.ui uibk\Progress.ui.bk_%curTime%
echo done.
:exit
pause