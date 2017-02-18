Rem This script requires Inno Setup
Rem Change paths to build, MinGW and Inno Setup!

set PKG_NAME=doublecontact_0.1.1_win32_portable
set PKG_DIR=..\..\%PKG_NAME%

call ..\make-bin-image.bat ..\.. ..\..\..\build-all-Qt_4_8_6_st-Release C:\Qt\2009.05\mingw %PKG_DIR%
copy doublecontact.ini %PKG_DIR%\doublecontact.ini

cd %PKG_DIR%\..
zip -r -9 %PKG_NAME%.zip %PKG_NAME%