if(${CMAKE_CXX_STANDARD} GREATER_EQUAL 11)
    set(RING_BUFFER_NOEXCEPT ON)
    message(STATUS "Enabling RING_BUFFER_NOEXCEPT (C++11 and up)")
endif()

if(${CMAKE_CXX_STANDARD} GREATER_EQUAL 14)
    set(RING_BUFFER_CONSTEXPR ON)
    message(STATUS "Enabling RING_BUFFER_CONSTEXPR (C++14 and up)")
endif()

try_compile(constexpr-destructors-compile ${CMAKE_BINARY_DIR}/detect ${CMAKE_SOURCE_DIR}/detect/constexpr_destructors.cpp
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED}
    CXX_EXTENSIONS ${CMAKE_CXX_EXTENSIONS}
)
if(constexpr-destructors-compile)
    set(RING_BUFFER_CONSTEXPR_DESTRUCTORS ON)
    message(STATUS "Enabling RING_BUFFER_CONSTEXPR_DESTRUCTORS (C++20 and up)")
endif()
