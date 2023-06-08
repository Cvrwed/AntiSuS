@echo off
setlocal
cls

set URL=https://raw.githubusercontent.com/zEncrypte/AntiSuS/main/domains-blacklisted.txt
set HOSTS_FILE=C:\Windows\System32\drivers\etc\hosts
set TEMP_FILE=%TEMP%\domains-blacklisted.txt

net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Permission denied.
    echo Run the script with administrator privileges.
    echo Press any key to exit.
    pause >nul
    exit /b
)

echo Fetching domain list...
curl -o domain-list.txt %URL%

echo Blacklisting sites...

findstr /x /c:"127.0.0.1 *" "%HOSTS_FILE%" > "%TEMP_FILE%"

findstr /v "^[#;]" domain-list.txt > filtered-list.txt
findstr /x /g:"%TEMP_FILE%" filtered-list.txt > existing-list.txt

set /a count=0
for /F "usebackq delims=" %%a in (filtered-list.txt) do (
    findstr /x "127.0.0.1     %%a" existing-list.txt >nul
    if errorlevel 1 (
        echo 127.0.0.1     %%a >> %HOSTS_FILE%
        echo Blacklisted %%a
        set /a count+=1
    )
)

echo Finished blacklisting sites! 
echo Total blocked domains: %count%
echo Press any key to close.
pause >nul

del domain-list.txt filtered-list.txt existing-list.txt "%TEMP_FILE%"

endlocal
