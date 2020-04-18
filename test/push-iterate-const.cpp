#include <vector>
#include <cassert>
#include <ring-buffer.h>

int main() {
    ring_buffer<int, 4> buf;
    const ring_buffer<int, 4>& const_buf = buf;

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    {
        std::vector<int> expected{3, 4, 5, 6};
        std::vector<int> actual;
        for (const int& i : const_buf) {
            actual.push_back(i);
        }
        assert(actual == expected);
    }

    buf.push_back(7);

    {
        std::vector<int> expected{4, 5, 6, 7};
        std::vector<int> actual;
        for (const int& i : const_buf) {
            actual.push_back(i);
        }
        assert(actual == expected);
    }
}
