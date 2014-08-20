cmake_minimum_required (VERSION 2.6)
project (gps_neighbour)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

add_executable(gps_file_binder main_file_binder.cpp file_binder.cpp)
add_executable(gps_neighbour main_gps_neighbour.cpp gps_neighbour.cpp)