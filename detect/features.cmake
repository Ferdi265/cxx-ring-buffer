if(cxx_noexcept IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(RING_BUFFER_NOEXCEPT ON)
    message(STATUS "Detected support for conditional noexcept")
endif()

if(cxx_constexpr IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(RING_BUFFER_CONSTEXPR ON)
    message(STATUS "Detected support for constexpr")
endif()

try_compile(constexpr-destructors-compile ${CMAKE_BINARY_DIR}/detect ${CMAKE_SOURCE_DIR}/detect/constexpr_destructors.cpp
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED}
    CXX_EXTENSIONS ${CMAKE_CXX_EXTENSIONS}
)
if(constexpr-destructors-compile)
    set(RING_BUFFER_CONSTEXPR_DESTRUCTORS ON)
    message(STATUS "Detected support for constexpr destructors")
endif()
