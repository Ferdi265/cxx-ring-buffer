try_compile(cxx-least-11 ${CMAKE_BINARY_DIR}/detect ${CMAKE_SOURCE_DIR}/detect/cxxstd.cpp
    COMPILE_DEFINITIONS -DCXX_STANDARD=201103
)

if(NOT cxx-least-11)
    message(FATAL_ERROR "This library requires at least C++11")
endif()

if(cxx-least-11)
    set(RING_BUFFER_NOEXCEPT ON)
    message(STATUS "Enabling RING_BUFFER_NOEXCEPT (C++11 and up)")
endif()

try_compile(cxx-least-14 ${CMAKE_BINARY_DIR}/detect ${CMAKE_SOURCE_DIR}/detect/cxxstd.cpp
    COMPILE_DEFINITIONS -DCXX_STANDARD=201402
)
if(cxx-least-14)
    set(RING_BUFFER_CONSTEXPR ON)
    message(STATUS "Enabling RING_BUFFER_CONSTEXPR (C++14 and up)")
endif()

try_compile(constexpr-destructors-compile ${CMAKE_BINARY_DIR}/detect ${CMAKE_SOURCE_DIR}/detect/constexpr_destructors.cpp)
if(constexpr-destructors-compile)
    set(RING_BUFFER_CONSTEXPR_DESTRUCTORS ON)
    message(STATUS "Enabling RING_BUFFER_CONSTEXPR_DESTRUCTORS (C++20 and up)")
endif()
