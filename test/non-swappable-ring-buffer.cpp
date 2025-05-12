#include <vector>
#include <cassert>
#include <ring-buffer.h>

struct non_swappable_array {
    using value_type = int;
    using size_type = size_t;
    int data[4];

    // non-copyable
    non_swappable_array() = default;
    non_swappable_array(const non_swappable_array&) = delete;
    non_swappable_array& operator=(const non_swappable_array&) = delete;

    size_t size() const {
        return 4;
    }

    int * begin() {
        return std::begin(data);
    }

    int * end() {
        return std::end(data);
    }

    const int * cbegin() const {
        return std::cbegin(data);
    }

    const int * cend() const {
        return std::cend(data);
    }

    int& operator[](size_t i) {
        return data[i];
    }

    const int& operator[](size_t i) const {
        return data[i];
    }

    // note: no swap implementation
};

int main() {
    basic_ring_buffer<non_swappable_array> buf;

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    {
        std::vector<int> expected{13, 14, 15, 16};
        std::vector<int> actual;
        for (int& i : buf) {
            i += 10;
            actual.push_back(i);
        }
        assert(actual == expected);
    }

    buf.push_back(7);

    {
        std::vector<int> expected{24, 25, 26, 17};
        std::vector<int> actual;
        for (int& i : buf) {
            i += 10;
            actual.push_back(i);
        }
        assert(actual == expected);
    }
}
