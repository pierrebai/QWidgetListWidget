@echo off
setlocal
mkdir Build
cd Build
set CMAKE_PREFIX_PATH=C:\Outils\Qt\5.12.1\msvc2017_64
cmake .. -G "Visual Studio 16 2019" -DCMAKE_GENERATOR_TOOLSET=v141
