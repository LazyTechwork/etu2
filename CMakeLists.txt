cmake_minimum_required(VERSION 3.21)
project(etu2)

set(CMAKE_CXX_STANDARD 23)

add_executable(etu2 main.cpp readers/WaveReader.cpp readers/WaveReader.h)
