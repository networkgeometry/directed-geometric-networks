cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(PGL_cpp_example)
set(CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(src/base_graph/include)

add_subdirectory(src/base_graph/src)

add_subdirectory(src)
