@echo off
set vcpkg=c:\vcpkg\installed\x64-windows
set libPath=%vcpkg%\lib
set includePath=%vcpkg%\include
@echo on
cl /EHsc /I%includePath% main.cc test.res /link /LIBPATH:%libPath% /out:a.exe /ENTRY:WinMainCRTStartup /SUBSYSTEM:CONSOLE