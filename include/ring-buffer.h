#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

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
    CONSTEXPR basic_ring_buffer() NOEXCEPT() = default;
    CONSTEXPR_D ~basic_ring_buffer() NOEXCEPT() = default;
    basic_ring_buffer(const basic_ring_buffer& other) = default;
    basic_ring_buffer(basic_ring_buffer&& other) = default;
    basic_ring_buffer& operator=(const basic_ring_buffer& other) = default;
    basic_ring_buffer& operator=(basic_ring_buffer&& other) = default;

    Container& buffer() {
        return container;
    }
    const Container& buffer() const {
        return container;
    }

    void push_back(const value_type& value) {
        container[front_index] = value;
        front_index = (front_index + 1) % container.size();
    }

    iterator begin() {
        return {container, front_index, 0};
    }
    iterator end() {
        return {container, front_index, container.size()};
    }

    const_iterator cbegin() const {
        return {container, front_index, 0};
    }
    const_iterator cend() const {
        return {container, front_index, container.size()};
    }
};

#include <array>
template <typename T, size_t N>
using ring_buffer = basic_ring_buffer<std::array<T, N>>;

#endif
