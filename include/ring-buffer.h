#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <array>
#include <utility>
#include <ring-buffer-config.h>
#include <ring-buffer-iterator.h>

template <typename Container>
class basic_ring_buffer {
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using iterator = ring_buffer_iterator<Container>;
    using const_iterator = ring_buffer_const_iterator<Container>;

private:
    Container container;
    size_type front_index{};

public:
    basic_ring_buffer() = default;
    ~basic_ring_buffer() = default;
    CONSTEXPR basic_ring_buffer(const Container& other) COND_NOEXCEPT(noexcept(Container(other))) : container(other) {}
    CONSTEXPR basic_ring_buffer(Container&& other) COND_NOEXCEPT(noexcept(Container(other))) : container(other) {}
    basic_ring_buffer(const basic_ring_buffer& other) = default;
    basic_ring_buffer(basic_ring_buffer&& other) = default;
    basic_ring_buffer& operator=(const basic_ring_buffer& other) = default;
    basic_ring_buffer& operator=(basic_ring_buffer&& other) = default;

    CONSTEXPR size_type size() const NOEXCEPT {
        return container.size();
    }

    CONSTEXPR value_type& operator[](size_type size) COND_NOEXCEPT(noexcept(container[size])) {
        return container[size];
    }
    CONSTEXPR const value_type& operator[](size_type size) const COND_NOEXCEPT(noexcept(container[size])) {
        return container[size];
    }

    CONSTEXPR Container& buffer() NOEXCEPT {
        return container;
    }
    CONSTEXPR const Container& buffer() const NOEXCEPT {
        return container;
    }

    CONSTEXPR void push_back(const value_type& value) COND_NOEXCEPT(noexcept(container[front_index] = value)) {
        container[front_index] = value;
        front_index = (front_index + 1) % container.size();
    }

    CONSTEXPR iterator begin() NOEXCEPT {
        return {container, front_index, 0};
    }
    CONSTEXPR iterator end() COND_NOEXCEPT(noexcept(container.size())) {
        return {container, front_index, container.size()};
    }

    CONSTEXPR const_iterator begin() const NOEXCEPT {
        return {container, front_index, 0};
    }
    CONSTEXPR const_iterator end() const COND_NOEXCEPT(noexcept(container.size())) {
        return {container, front_index, container.size()};
    }

    CONSTEXPR const_iterator cbegin() const NOEXCEPT {
        return {container, front_index, 0};
    }
    CONSTEXPR const_iterator cend() const COND_NOEXCEPT(noexcept(container.size())) {
        return {container, front_index, container.size()};
    }
};

template <typename T, size_t N>
using ring_buffer = basic_ring_buffer<std::array<T, N>>;

#endif
