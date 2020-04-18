cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(test-project CXX)

option(RING_BUFFER_BUILD_TESTS "build test cases for the ring buffer library" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ring-buffer INTERFACE)
target_include_directories(ring-buffer INTERFACE include/)

if(RING_BUFFER_BUILD_TESTS)
    add_subdirectory(test)
endif()
