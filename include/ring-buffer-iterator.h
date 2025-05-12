#ifndef _RING_BUFFER_ITERATOR_H
#define _RING_BUFFER_ITERATOR_H

#include <iterator>
#include <utility>
#include <ring-buffer-config.h>

template <typename Container>
class ring_buffer_iterator {
private:
    using size_type = typename Container::size_type;
    using value_type = typename std::iterator_traits<ring_buffer_iterator>::value_type;
    using difference_type = typename std::iterator_traits<ring_buffer_iterator>::difference_type;
    using reference = typename std::iterator_traits<ring_buffer_iterator>::reference;
    using pointer = typename std::iterator_traits<ring_buffer_iterator>::pointer;

    Container *container_ptr;
    size_type front;
    size_type index;

public:
    ring_buffer_iterator() = default;
    ~ring_buffer_iterator() = default;
    CONSTEXPR ring_buffer_iterator(Container &container, size_type front = 0, size_type index = 0) NOEXCEPT : container_ptr(&container), front(front), index(index) {}
    ring_buffer_iterator(const ring_buffer_iterator&) = default;
    ring_buffer_iterator(ring_buffer_iterator&&) = default;
    ring_buffer_iterator& operator=(const ring_buffer_iterator&) = default;
    ring_buffer_iterator& operator=(ring_buffer_iterator&&) = default;

    CONSTEXPR ring_buffer_iterator& operator+=(difference_type n) NOEXCEPT {
        index += n;
    }
    CONSTEXPR ring_buffer_iterator& operator-=(difference_type n) NOEXCEPT {
        index -= n;
    }

    CONSTEXPR ring_buffer_iterator operator+(difference_type n) const NOEXCEPT {
        return {*container_ptr, front, index + n};
    }
    CONSTEXPR ring_buffer_iterator operator-(difference_type n) const NOEXCEPT {
        return {*container_ptr, front, index - n};
    }

    CONSTEXPR difference_type operator-(const ring_buffer_iterator& other) const NOEXCEPT {
        return index - other.index;
    }

    CONSTEXPR reference operator*() COND_NOEXCEPT(noexcept(container_ptr->begin()) && noexcept(container_ptr->size())) {
        return *(container_ptr->begin() + (front + index) % container_ptr->size());
    }
    CONSTEXPR pointer operator->() COND_NOEXCEPT(noexcept(container_ptr->begin()) && noexcept(container_ptr->size())) {
        return &**this;
    }
    CONSTEXPR reference operator[](difference_type n) COND_NOEXCEPT(noexcept(container_ptr->begin()) && noexcept(container_ptr->size())) {
        return *(*this + n);
    }

    CONSTEXPR ring_buffer_iterator& operator++() NOEXCEPT {
        index++;
        return *this;
    }
    CONSTEXPR ring_buffer_iterator operator++(int) NOEXCEPT {
        ring_buffer_iterator old = *this;
        *this++;
        return old;
    }
    CONSTEXPR ring_buffer_iterator& operator--() NOEXCEPT {
        index--;
        return *this;
    }
    CONSTEXPR ring_buffer_iterator operator--(int) NOEXCEPT {
        ring_buffer_iterator old = *this;
        *this--;
        return old;
    }

    CONSTEXPR bool operator==(const ring_buffer_iterator& other) const NOEXCEPT {
        return index == other.index;
    }
    CONSTEXPR bool operator!=(const ring_buffer_iterator& other) const NOEXCEPT {
        return index != other.index;
    }

    CONSTEXPR bool operator<(const ring_buffer_iterator& other) const NOEXCEPT {
        return index < other.index;
    }
    CONSTEXPR bool operator>(const ring_buffer_iterator& other) const NOEXCEPT {
        return index > other.index;
    }
    CONSTEXPR bool operator<=(const ring_buffer_iterator& other) const NOEXCEPT {
        return index <= other.index;
    }
    CONSTEXPR bool operator>=(const ring_buffer_iterator& other) const NOEXCEPT {
        return index >= other.index;
    }

    CONSTEXPR friend ring_buffer_iterator operator+(difference_type n, const ring_buffer_iterator& it) NOEXCEPT {
        return it + n;
    }
    CONSTEXPR friend void swap(ring_buffer_iterator& a, ring_buffer_iterator& b) COND_NOEXCEPT(noexcept(std::swap(a.container_ptr, b.container_ptr))) {
        using std::swap;
        swap(a.container_ptr, b.container_ptr);
        swap(a.front, b.front);
        swap(a.index, b.index);
    }
};

template <typename Container>
class ring_buffer_const_iterator {
private:
    using size_type = typename Container::size_type;
    using value_type = typename std::iterator_traits<ring_buffer_const_iterator>::value_type;
    using difference_type = typename std::iterator_traits<ring_buffer_const_iterator>::difference_type;
    using reference = typename std::iterator_traits<ring_buffer_const_iterator>::reference;
    using pointer = typename std::iterator_traits<ring_buffer_const_iterator>::pointer;

    const Container *container_ptr;
    size_type front;
    size_type index;

public:
    ring_buffer_const_iterator() = default;
    ~ring_buffer_const_iterator() = default;
    CONSTEXPR ring_buffer_const_iterator(const Container &container, size_type front = 0, size_type index = 0) NOEXCEPT : container_ptr(&container), front(front), index(index) {}
    ring_buffer_const_iterator(const ring_buffer_const_iterator&) = default;
    ring_buffer_const_iterator(ring_buffer_const_iterator&&) = default;
    ring_buffer_const_iterator& operator=(const ring_buffer_const_iterator&) = default;
    ring_buffer_const_iterator& operator=(ring_buffer_const_iterator&&) = default;

    CONSTEXPR ring_buffer_const_iterator& operator+=(difference_type n) NOEXCEPT {
        index += n;
    }
    CONSTEXPR ring_buffer_const_iterator& operator-=(difference_type n) NOEXCEPT {
        index -= n;
    }

    CONSTEXPR ring_buffer_const_iterator operator+(difference_type n) const NOEXCEPT {
        return {*container_ptr, front, index + n};
    }
    CONSTEXPR ring_buffer_const_iterator operator-(difference_type n) const NOEXCEPT {
        return {*container_ptr, front, index - n};
    }

    CONSTEXPR difference_type operator-(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index - other.index;
    }

    CONSTEXPR reference operator*() const COND_NOEXCEPT(noexcept(container_ptr->cbegin()) && noexcept(container_ptr->size())) {
        return *(container_ptr->cbegin() + (front + index) % container_ptr->size());
    }
    CONSTEXPR pointer operator->() const COND_NOEXCEPT(noexcept(container_ptr->cbegin()) && noexcept(container_ptr->size())) {
        return &**this;
    }
    CONSTEXPR reference operator[](difference_type n) COND_NOEXCEPT(noexcept(container_ptr->cbegin()) && noexcept(container_ptr->size())) {
        return *(*this + n);
    }

    CONSTEXPR ring_buffer_const_iterator& operator++() NOEXCEPT {
        index++;
        return *this;
    }
    CONSTEXPR ring_buffer_const_iterator operator++(int) NOEXCEPT {
        ring_buffer_const_iterator old = *this;
        *this++;
        return old;
    }
    CONSTEXPR ring_buffer_const_iterator& operator--() NOEXCEPT {
        index--;
        return *this;
    }
    CONSTEXPR ring_buffer_const_iterator operator--(int) NOEXCEPT {
        ring_buffer_const_iterator old = *this;
        *this--;
        return old;
    }

    CONSTEXPR bool operator==(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index == other.index;
    }
    CONSTEXPR bool operator!=(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index != other.index;
    }

    CONSTEXPR bool operator<(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index < other.index;
    }
    CONSTEXPR bool operator>(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index > other.index;
    }
    CONSTEXPR bool operator<=(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index <= other.index;
    }
    CONSTEXPR bool operator>=(const ring_buffer_const_iterator& other) const NOEXCEPT {
        return index >= other.index;
    }

    CONSTEXPR friend ring_buffer_const_iterator operator+(difference_type n, const ring_buffer_const_iterator& it) NOEXCEPT {
        return it + n;
    }
    CONSTEXPR friend void swap(ring_buffer_const_iterator& a, ring_buffer_const_iterator& b) COND_NOEXCEPT(noexcept(std::swap(a.container_ptr, b.container_ptr))) {
        using std::swap;
        swap(a.container_ptr, b.container_ptr);
        swap(a.front, b.front);
        swap(a.index, b.index);
    }
};

namespace std {
    template <typename Container>
    class iterator_traits<ring_buffer_iterator<Container>> {
    public:
        using difference_type = typename std::make_signed<typename Container::size_type>::type;
        using value_type = typename Container::value_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::random_access_iterator_tag;
    };

    template <typename Container>
    class iterator_traits<ring_buffer_const_iterator<Container>> {
    public:
        using difference_type = typename std::make_signed<typename Container::size_type>::type;
        using value_type = const typename Container::value_type;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::random_access_iterator_tag;
    };
}

#endif
