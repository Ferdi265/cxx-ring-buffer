# cxx-ring-buffer

a small header-only implementation of a C++ ring-buffer container wrapper and
STL-style iterators.

## Overview

This project provides the following types:

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

The last 3 options set preprocessor defines with the same name when enabled,
and may be automatically enabled when `RING_BUFFER_FEATURE_DETECT` is enabled.

## Preprocessor defines

- `RING_BUFFER_NOEXCEPT`  
  enable use of the `noexcept(bool-expr)` conditional noexcept operator (needs C++11)
- `RING_BUFFER_CONSTEXPR`  
  make all member functions of `basic_ring_buffer` and its iterators `constexpr` (needs C++14)
- `RING_BUFFER_CONSTEXPR_DESTRUCTORS`  
  make the destructors of `basic_ring_buffer` and its iterators explicitly `constexpr` (needs C++20)

## Documentation

All member functions and constructors of the following types are `constexpr` if
the `RING_BUFFER_CONSTEXPR` feature is enabled.

All member functions and constructors of the following types are `noexcept` or
conditionally `noexcept` if the `RING_BUFFER_NOEXCEPT` feature is enabled.

Destructors of the following types are explicitly marked as `constexpr` if the
`RING_BUFFER_CONSTEXPR_DESTRUCTORS` feature is enabled.

### `class ring_buffer<T, N>`
(defined in `<ring-buffer.h>`)

`ring_buffer` is an alias template resolving to
`basic_ring_buffer<std::array<T, N>>`.

### `class basic_ring_buffer<Container>`
(defined in `<ring-buffer.h>`)

`basic_ring_buffer` is a template class wrapping a container, providing a
`push_back(value)` method that treats the container as a ring buffer, and an
STL-style iterator interface to iterate over the wrapped container.

Use of the `push_back(value)` method replaces the oldest element in the
underlying container, and moves the logical first element one further. (i.e.,
the logical first element is always the oldest element in the underlying
container).

The iterators returned by `begin()`, `end()`, `begin() const`, `end() const`,
`cbegin() const`, and `cend() const` start at the logical first element and end
after the logical last element. (i.e., they wrap around if they reach the end of
the underlying container)

`basic_ring_buffer` fulfills its own template parameter requirements.

#### Template parameter requirements

The parameter `Container` needs to have member types `value_type` and
`size_type`, and methods `size_type size() const`, `iterator begin()`,
`iterator end()`, `const_iterator cbegin() const`, and `const_iterator cend()
const`, as well as an overloaded `value_type& operator[](size_type)` and `const
value_type& operator[](size_type) const)`.

The iterators returned by the container need to be random access iterators.

#### Member Types

- `value_type`:  
    the `value_type` of the underlying container, as well as the `value_type` of
    the provided iterators.
- `size_type`:  
    the `size_type` of the underlying container.
- `iterator`:  
    the type of iterators returned by `begin()` and `end()`:
    `ring_buffer_iterator<Container>`.
- `const_iterator`:  
    the type of iterators returned by `begin() const`, `end() const`, `cbegin()
    const`, and `cend() const`: `ring_buffer_const_iterator<Container>`.

#### Constructors

- `basic_ring_buffer()`:  
    default constructs the wrapped container and value-initializes the internal
    `front_index` variable of `size_type`.
- `basic_ring_buffer(const Container&)`:  
    copy-constructs the container and value-initializes the internal
    `front_index` variable of `size_type`.
- `basic_ring_buffer(Container&&)`:  
    move-constructs the container and value-initializes the internal
    `front_index` variable of `size_type`.
- `basic_ring_buffer(const basic_ring_buffer&)`:  
    copy-constructs a `basic_ring_buffer` from another instance with the same
    container type.
- `basic_ring_buffer(const basic_ring_buffer&&)`:  
    move-constructs a `basic_ring_buffer` from another instance with the same
    container type.

#### Operators

- `basic_ring_buffer& operator=(const basic_ring_buffer&)`:  
    copy-assigns a `basic_ring_buffer` with the same container type to this
    instance.
- `basic_ring_buffer& operator=(const basic_ring_buffer&&)`:  
    move-assigns a `basic_ring_buffer` with the same container type to this
    instance.

#### Methods

- `Container& buffer()`:  
    returns a reference to the underlying buffer
- `const Container& buffer() const`:  
    returns a const reference to the underlying buffer
- `void push_back(const value_type& value)`:  
    inserts a new element into the buffer, replacing the least-recently inserted
    element. This operation will appear to remove the first element and insert
    a new element in the back when using a `ring_buffer_iterator`.  
    e.g., if the container has length 6, with elements 'a', 'b', 'c', 'd', 'e',
    'f', and `push_back('g')` is called, the elements will be 'g', 'b', 'c',
    'd', e', 'f', and a future call to `begin()` will return an iterator to 'b'.
- `iterator begin()`:  
    returns a `ring_buffer_iterator` to the logical first element of the
    container.  
    e.g., if the container has length 6, with elements 'a', 'b', 'c', 'd', 'e',
    'f', and `push_back('g')` was called, the elements will be 'g', 'b', 'c',
    'd', e', 'f', and a call to `begin()` will return an iterator to 'b'.
- `iterator end()`:  
    returns a `ring_buffer_iterator` to the logical one-after-last element of
    the container so that itertion stops after the logical last element of the
    container.
- `const_iterator begin() const`:  
    returns a `ring_buffer_const_iterator` to the logical first element of the
    container.
- `const_iterator end() const`:  
    returns a `ring_buffer_const_iterator` to the logical one-after-last element
    of the container.
- `const_iterator cbegin() const`:  
    returns a `ring_buffer_const_iterator` to the logical first element of the
    container.
- `const_iterator cend() const`:  
    returns a `ring_buffer_const_iterator` to the logical one-after-last element
    of the container.

### `class ring_buffer_iterator<Container>`
(defined in `<ring-buffer-iterator.h>`)

`ring_buffer_iterator` is a template class providing an iterator usable for
iterating over a container in a ring-buffer-like fashion, i.e., start at an
index other than 0, and wrap around when the end of the container is reached.

`ring_buffer_iterator` is a random access iterator and fulfills the
requirements of the C++ named requirement
[LegacyRandomAccessIterator][lra-iter].

#### Template parameter requirements

The parameter `Container` needs to fulfill the same requirements as for
`basic_ring_buffer`.

### `class ring_buffer_const_iterator<Container>`
(defined in `<ring-buffer-iterator.h>`)

`ring_buffer_const_iterator` is a template class providing an iterator usable
for iterating over a container in a ring-buffer-like fashion, i.e., start at an
index other than 0, and wrap around when the end of the container is reached.

`ring_buffer_const_iterator` is a random access iterator and fulfills the
requirements of the C++ named requirement
[LegacyRandomAccessIterator][lra-iter].

#### Template parameter requirements

The parameter `Container` needs to fulfill the same requirements as for
`basic_ring_buffer`.

[lra-iter]: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
