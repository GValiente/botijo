# botijo

botijo is a small multi-platform C++11 library for building 2D games and other graphical applications with sprites.

It works on Linux, Windows and MacOS.

## Requirements

Since SDL2 and GLEW come bundled with this library, there's no external dependencies required, so the only software requirements are a C++11-compatible compiler and CMake >= 3.4.

botijo has been tested with these compilers:

* GCC 4.9.
* MSVC 2017.
* Whatever Clang comes with Apple LLVM 9.1.0.

## How to build

A CMakeLists.txt is provided with this library, so in order to use it you only need to include this file in your CMake project.  

To build and run the unit tests, you need to generate them first:

```
mkdir build
cd build
cmake -DBTJ_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..
make
./tests/botijo-tests
```
