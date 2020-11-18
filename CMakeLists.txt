cmake_minimum_required(VERSION 2.8.12)
project(Zephyr3D)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")

file(GLOB_RECURSE Zephyr3D_HEADERS "include/*.h" "include/*.cpp")
file(GLOB_RECURSE Zephyr3D_SHADERS "include/*.frag" "include/*.vert")

add_subdirectory(include/Zephyr3D)
add_subdirectory(example)
add_compile_definitions(CONFIGURATION="$(ConfigurationName)")