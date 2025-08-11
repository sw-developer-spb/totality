@echo off
:: call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
cmake --preset default
cmake --build --preset default
::set CMAKE_INSTALL_PREFIX=%CD%\dist
cmake --install build --prefix dist --config Debug
