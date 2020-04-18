#include <array>
#include <ring-buffer.h>

#ifdef RING_BUFFER_CONSTEXPR
template <typename T, size_t N>
constexpr bool array_equal(const std::array<T, N>& a, const std::array<T, N>& b) {
    for (size_t i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }

    return true;
}

constexpr bool test() {
    std::array<int, 4> init{0, 0, 0, 0};
    ring_buffer<int, 4> buf(init);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    {
        std::array<int, 4> expected{13, 14, 15, 16};
        std::array<int, 4> actual{0, 0, 0, 0};
        int actual_index = 0;
        for (int& i : buf) {
            i += 10;
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    buf.push_back(7);

    {
        std::array<int, 4> expected{24, 25, 26, 17};
        std::array<int, 4> actual{0, 0, 0, 0};
        int actual_index = 0;
        for (int& i : buf) {
            i += 10;
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    return true;
}

static_assert(test());
#endif

int main() {}
