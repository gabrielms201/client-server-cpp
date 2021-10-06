@echo off
if not exist "build" mkdir "build"
cd "build"
cmake -T v141 -A x64 ..
pause
