@echo off

rem Compile the C++ code
g++ -Wall main.cpp -o ..\commandLineCash.exe

if errorlevel 1 (
  echo Error: Compilation failed!
  exit /b 1
)

rem Run the compiled program
..\commandLineCash.exe  # 

echo Program execution complete.
