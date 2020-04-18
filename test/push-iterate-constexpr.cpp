#include <array>
#include <ring-buffer.h>

#ifdef RING_BUFFER_CONSTEXPR
#include "constexpr-array-shim.h"

template <typename T, size_t N>
constexpr bool array_equal(const constexpr_array<T, N>& a, const constexpr_array<T, N>& b) {
    for (size_t i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }

    return true;
}

constexpr bool test() {
    constexpr_array<int, 4> init{0, 0, 0, 0};
    basic_ring_buffer<constexpr_array<int, 4>> buf(init);

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    {
        constexpr_array<int, 4> expected{13, 14, 15, 16};
        constexpr_array<int, 4> actual{0, 0, 0, 0};
        int actual_index = 0;
        for (int& i : buf) {
            i += 10;
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    buf.push_back(7);

    {
        constexpr_array<int, 4> expected{24, 25, 26, 17};
        constexpr_array<int, 4> actual{0, 0, 0, 0};
        int actual_index = 0;
        for (int& i : buf) {
            i += 10;
            actual[actual_index++] = i;
        }
        if (!array_equal(actual, expected)) return false;
    }

    return true;
}

static_assert(test(), "");
#endif

int main() {}
