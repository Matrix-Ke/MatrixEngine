cd /d %~dp0

@echo off
setlocal enabledelayedexpansion
for /f "delims=" %%i in ('dir /b *VS*') do (
    echo %%i
    set var=%%i
    set var=!var:VS=!
    echo %%i !var!
    ren "%%i" "!var!"
)
pause
