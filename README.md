# totality
The thing for file search.

[prerequisits]
Qt
    add c:\Qt\6.5.3\msvc2019_64\bin\ to evn.var PATH
VS2022


[build]
without presets
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/6.5.3/msvc2019_64" 
cmake --build build --config Debug

with preset
cmake --preset default         # Configure (generates build files)
cmake --build --preset default # Build using the preset's build directory and generator

to debug cmake
    cmake --preset default --trace-expand > qt.txt 2>&1

[run]
totality\build\Debug\totality.exe

[edit]
totality\build\totality.sln