cmake_minimum_required(VERSION 3.3)
project(helios)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/main.cpp source/math/vector/vec3.h source/math/vector/vec3.cpp)
add_executable(helios ${SOURCE_FILES})

include_directories("source/math/vector")