#include <array>
#include <ring-buffer.h>

template <typename T, size_t N>
constexpr bool array_equal(const std::array<T, N>& a, const std::array<T, N>& b) {
    for (size_t i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }

    return true;
}

constexpr bool test() {
    ring_buffer<int, 4> buf;
    const ring_buffer<int, 4>& const_buf = buf;

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    {
        std::array<int, 4> expected{3, 4, 5, 6};
        std::array<int, 4> actual;
        int actual_index = 0;
        for (const int& i : const_buf) {
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    buf.push_back(7);

    {
        std::array<int, 4> expected{4, 5, 6, 7};
        std::array<int, 4> actual;
        int actual_index = 0;
        for (const int& i : const_buf) {
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    return true;
}

static_assert(test());

int main() {}
