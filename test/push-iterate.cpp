#include <vector>
#include <cassert>
#include <ring-buffer.h>

int main() {
    ring_buffer<int, 4> buf;

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
