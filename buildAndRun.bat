@echo off
setlocal

set DIRECTORY=.\build
set FILENAME=Network_Simulator.exe

if not exist "%DIRECTORY%" (
    mkdir "%DIRECTORY%"
)

if exist "%DIRECTORY%\%FILENAME%" (
    del "%DIRECTORY%\%FILENAME%"
)

cd "%DIRECTORY%"
cmake ..
make

"%DIRECTORY%\%FILENAME%"
