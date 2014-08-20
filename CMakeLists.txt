cmake_minimum_required (VERSION 2.6)
project (gps_file_binder)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

add_executable(gps_file_binder main.cpp file_binder.cpp)