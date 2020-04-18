# cxx-ring-buffer

a small implementation of a C++ ring-buffer container wrapper and STL-style
iterators.

## Overview

This projects provides the following types:

- the template `basic_ring_buffer<ContainerType>`, defined in `<ring-buffer.h>`  
  augments an existing container to be used as a ring buffer
- the alias template `ring_buffer<ValueType, Size>`, defined in `<ring-buffer.h>`  
  an alias for `basic_ring_buffer<std::array<ValueType, Size>>`
- the template `ring_buffer_iterator<ContainerType>`, defined in `<ring-buffer-iterator.h>`  
  a random access iterator over a `basic_ring_buffer` with the same container type
- the template `ring_buffer_const_iterator<ContainerType>`, defined in `<ring-buffer-iterator.h>`  
  a random access iterator over a `basic_ring_buffer` with the same container type,
  giving `const` access to the elements

This project can be configured via CMake options or preprocessor defines

## CMake options

- `RING_BUFFER_DEFAULT_CXXFLAGS` (default OFF)  
  set the C++ compiler flags to `-Wall -Wextra`, and try to detect the newest supported C++ standard.
- `RING_BUFFER_BUILD_TESTS` (default OFF)  
  build the test programs from the `test/` subdirectory
- `RING_BUFFER_FEATURE_DETECT` (default ON)  
  try to detect the values for the following feature options automatically
- `RING_BUFFER_NOEXCEPT` (default OFF)  
  enable use of the `noexcept(bool-expr)` conditional noexcept operator (needs C++11)
- `RING_BUFFER_CONSTEXPR` (default OFF)  
  make all member functions of `basic_ring_buffer` and its iterators `constexpr` (needs C++14)
- `RING_BUFFER_CONSTEXPR_DESTRUCTORS` (default OFF)  
  make the destructors of `basic_ring_buffer` and its iterators explicitly `constexpr` (needs C++20)

The last 3 options set preprocessor defines with the same name when enabled.

## Preprocessor defines

- `RING_BUFFER_NOEXCEPT` (default OFF)  
  enable use of the `noexcept(bool-expr)` conditional noexcept operator (needs C++11)
- `RING_BUFFER_CONSTEXPR` (default OFF)  
  make all member functions of `basic_ring_buffer` and its iterators `constexpr` (needs C++14)
- `RING_BUFFER_CONSTEXPR_DESTRUCTORS` (default OFF)  
  make the destructors of `basic_ring_buffer` and its iterators explicitly `constexpr` (needs C++20)
