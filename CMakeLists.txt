cmake_minimum_required(VERSION 3.3)
project(helios)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/main.cpp source/math/vector/vec3.h
        source/math/vector/vec3.cpp source/renderer/renderer.h
        source/renderer/ray_tracer.h source/renderer/ray_tracer.cpp
        source/geometry/object.h source/material/material.h
        source/geometry/sphere.h source/geometry/sphere.cpp source/math/ray/ray.h
        source/math/ray/ray.cpp source/geometry/box.h source/geometry/box.cpp source/math/matrix/mat4.h
        source/math/matrix/mat4.cpp source/scene/scene.h source/scene/scene.cpp source/image/image.h
        source/image/ppm_image.h source/image/ppm_image.cpp)

include_directories("source/math/vector")
include_directories("source/math/ray")
include_directories("source/math/matrix")
include_directories("source/renderer")
include_directories("source/geometry")
include_directories("source/material")
include_directories("source/scene")
include_directories("source/image")

add_executable(helios ${SOURCE_FILES})