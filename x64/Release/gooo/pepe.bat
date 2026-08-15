@echo off
openfiles >nul 2>nul
if %errorlevel% neq 0 (
    echo This script is not running as Administrator. Re-launching with admin privileges...
    powershell -Command "Start-Process cmd -ArgumentList '/c ""%~s0""' -Verb runAs"
    exit /b
)

pushd "%cd%"
cd /d "%~dp0"

cd /d "%~dp0"
echo.
set "file_path=Sync.dll"
echo ok, using: "%file_path%"
echo.

:: === use signtool instead of relapse-signer ===
"%cd%\signer\signtool\signtool.exe" sign ^
/f "%cd%\certificates\1.pfx" ^
/p "ndasec-2016" ^
/tr http://timestamp.digicert.com ^
/td sha256 ^
/fd sha256 ^
"%file_path%"

echo.
echo done signing: "%file_path%"
pause
