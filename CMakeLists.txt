cmake_minimum_required (VERSION 2.6)
project (gps_neighbour)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

add_executable(gps_neighbour main.cpp gps_neighbour.cpp)