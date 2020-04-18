#include <type_traits>
#include <utility>
#include <iterator>

template <typename Container>
class ring_buffer_iterator {
private:
    using size_type = typename Container::size_type;
    using value_type = typename std::iterator_traits<ring_buffer_iterator>::value_type;
    using difference_type = typename std::iterator_traits<ring_buffer_iterator>::difference_type;
    using reference = typename std::iterator_traits<ring_buffer_iterator>::reference;
    using pointer = typename std::iterator_traits<ring_buffer_iterator>::pointer;

    Container* container;
    size_type front;
    size_type index;

public:
    ring_buffer_iterator() = default;
    ~ring_buffer_iterator() = default;
    ring_buffer_iterator(Container& container, size_type front = 0, size_type index = 0) : container(&container), front(front), index(index) {}
    ring_buffer_iterator(const ring_buffer_iterator&) = default;
    ring_buffer_iterator(ring_buffer_iterator&&) = default;
    ring_buffer_iterator& operator=(const ring_buffer_iterator&) = default;
    ring_buffer_iterator& operator=(ring_buffer_iterator&&) = default;

    ring_buffer_iterator& operator+=(difference_type n) {
        index += n;
    }
    ring_buffer_iterator& operator-=(difference_type n) {
        index -= n;
    }

    ring_buffer_iterator operator+(difference_type n) const {
        return {container, front, index + n};
    }
    ring_buffer_iterator operator-(difference_type n) const {
        return {container, front, index - n};
    }

    reference operator*() {
        return *(container->begin() + (front + index) % container->size());
    }
    pointer operator->() {
        return &**this;
    }
    reference operator[](difference_type n) {
        return *(*this + n);
    }

    ring_buffer_iterator& operator++() {
        index++;
        return *this;
    }
    ring_buffer_iterator operator++(int) {
        ring_buffer_iterator old = *this;
        *this++;
        return old;
    }
    ring_buffer_iterator& operator--() {
        index--;
        return *this;
    }
    ring_buffer_iterator operator--(int) {
        ring_buffer_iterator old = *this;
        *this--;
        return old;
    }

    bool operator==(const ring_buffer_iterator& other) const {
        return index == other.index;
    }
    bool operator!=(const ring_buffer_iterator& other) const {
        return index != other.index;
    }

    bool operator<(const ring_buffer_iterator& other) const {
        return index < other.index;
    }
    bool operator>(const ring_buffer_iterator& other) const {
        return index > other.index;
    }
    bool operator<=(const ring_buffer_iterator& other) const {
        return index <= other.index;
    }
    bool operator>=(const ring_buffer_iterator& other) const {
        return index >= other.index;
    }

    friend ring_buffer_iterator operator+( difference_type n, const ring_buffer_iterator& it) {
        return it + n;
    }
    friend void swap(ring_buffer_iterator& a, ring_buffer_iterator& b) {
        using std::swap;
        swap(a.container, b.container);
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

    const Container* container;
    size_type front{};
    size_type index{};

public:
    ring_buffer_const_iterator() = default;
    ~ring_buffer_const_iterator() = default;
    ring_buffer_const_iterator(const Container& container, size_type front = 0, size_type index = 0) : container(&container), front(front), index(index) {}
    ring_buffer_const_iterator(const ring_buffer_const_iterator&) = default;
    ring_buffer_const_iterator(ring_buffer_const_iterator&&) = default;
    ring_buffer_const_iterator& operator=(const ring_buffer_const_iterator&) = default;
    ring_buffer_const_iterator& operator=(ring_buffer_const_iterator&&) = default;

    ring_buffer_const_iterator& operator+=(difference_type n) {
        index += n;
    }
    ring_buffer_const_iterator& operator-=(difference_type n) {
        index -= n;
    }

    ring_buffer_const_iterator operator+(difference_type n) const {
        return {container, front, index + n};
    }
    ring_buffer_const_iterator operator-(difference_type n) const {
        return {container, front, index - n};
    }

    reference operator*() const {
        return *(container->begin() + (front + index) % container->size());
    }
    pointer operator->() const {
        return &**this;
    }
    reference operator[](difference_type n) const {
        return *(*this + n);
    }

    ring_buffer_const_iterator& operator++() {
        index++;
        return *this;
    }
    ring_buffer_const_iterator operator++(int) {
        ring_buffer_const_iterator old = *this;
        *this++;
        return old;
    }
    ring_buffer_const_iterator& operator--() {
        index--;
        return *this;
    }
    ring_buffer_const_iterator operator--(int) {
        ring_buffer_const_iterator old = *this;
        *this--;
        return old;
    }

    bool operator==(const ring_buffer_const_iterator& other) const {
        return index == other.index;
    }
    bool operator!=(const ring_buffer_const_iterator& other) const {
        return index != other.index;
    }

    bool operator<(const ring_buffer_const_iterator& other) const {
        return index < other.index;
    }
    bool operator>(const ring_buffer_const_iterator& other) const {
        return index > other.index;
    }
    bool operator<=(const ring_buffer_const_iterator& other) const {
        return index <= other.index;
    }
    bool operator>=(const ring_buffer_const_iterator& other) const {
        return index >= other.index;
    }

    friend ring_buffer_const_iterator operator+( difference_type n, const ring_buffer_const_iterator& it) {
        return it + n;
    }
    friend void swap(ring_buffer_const_iterator& a, ring_buffer_const_iterator& b) {
        using std::swap;
        swap(a.container, b.container);
        swap(a.front, b.front);
        swap(a.index, b.index);
    }
};

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
    basic_ring_buffer() noexcept = default;
    ~basic_ring_buffer() noexcept = default;
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

#include <array>
template <typename T, size_t N>
using ring_buffer = basic_ring_buffer<std::array<T, N>>;
