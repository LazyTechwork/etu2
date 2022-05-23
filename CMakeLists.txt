cmake_minimum_required(VERSION 3.21)
project(etu2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(lib_wave libraries/lib_wave.cpp readers/WaveReader.cpp readers/WaveReader.h terminal/Histogram.cpp terminal/Histogram.h terminal/Keyboard.h)
add_executable(lib_bmpcode libraries/lib_bmpcode.cpp cli_tools/ArgsParser.cpp cli_tools/ArgsParser.h writers/BitmapWriter.cpp writers/BitmapWriter.h commons/BitmapStructs.h cli_tools/Loader.cpp cli_tools/Loader.h)
add_executable(lib_bytelysis libraries/lib_bytelysis.cpp cli_tools/ArgsParser.cpp cli_tools/ArgsParser.h cli_tools/Loader.cpp cli_tools/Loader.h)
