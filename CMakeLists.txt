cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(test-project CXX)

option(RING_BUFFER_CXXFLAGS "enable default CXXFLAGS" ON)
option(RING_BUFFER_BUILD_TESTS "build test cases for the ring buffer library" ON)

option(RING_BUFFER_FEATURE_DETECT "try to detect if c++ features are supported" ON)
option(RING_BUFFER_NOEXCEPT "enable conditionally noexcept ring_buffer (c++11)" OFF)
option(RING_BUFFER_CONSTEXPR "enable constexpr ring_buffer (c++14)" OFF)
option(RING_BUFFER_CONSTEXPR_DESTRUCTORS "enable constexpr destructor for ring_buffer (c++20)" OFF)

if(RING_BUFFER_CXXFLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    include(detect/standard.cmake)
endif()

if(RING_BUFFER_FEATURE_DETECT)
    include(detect/features.cmake)
endif()

add_library(ring-buffer INTERFACE)
target_include_directories(ring-buffer INTERFACE include/)
target_compile_features(ring-buffer INTERFACE cxx_std_11)

if(RING_BUFFER_CONSTEXPR)
    target_compile_definitions(ring-buffer INTERFACE RING_BUFFER_CONSTEXPR)
endif()
if(RING_BUFFER_NOEXCEPT)
    target_compile_definitions(ring-buffer INTERFACE RING_BUFFER_NOEXCEPT)
endif()
if(RING_BUFFER_CONSTEXPR_DESTRUCTORS)
    target_compile_definitions(ring-buffer INTERFACE RING_BUFFER_CONSTEXPR_DESTRUCTORS)
endif()

if(RING_BUFFER_BUILD_TESTS)
    add_subdirectory(test)
endif()
