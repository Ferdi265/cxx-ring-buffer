#ifndef _CONSTEXPR_ARRAY_SHIM_H
#define _CONSTEXPR_ARRAY_SHIM_H

#include <array>

#if defined( __cpp_lib_array_constexpr) && __cpp_lib_array_constexpr >= 201606L
template <typename T, size_t N>
using constexpr_array = std::array<T, N>;
#else
template <typename T, size_t N>
struct constexpr_array {
    using size_type = size_t;
    using value_type = T;

    T data[N];

    constexpr size_t size() const {
        return N;
    }

    constexpr T* begin() {
        return data;
    }

    constexpr T* end() {
        return &data[N];
    }

    constexpr const T* begin() const {
        return data;
    }

    constexpr const T* end() const {
        return &data[N];
    }

    constexpr const T* cbegin() const {
        return data;
    }

    constexpr const T* cend() const {
        return &data[N];
    }

    constexpr T& operator[](size_t index) {
        return data[index];
    }

    constexpr const T& operator[](size_t index) const {
        return data[index];
    }
};

#endif

#endif
