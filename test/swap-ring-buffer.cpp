#include <vector>
#include <cassert>
#include <ring-buffer.h>
#include <utility>

int main() {
    ring_buffer<int, 4> buf1;

    buf1.push_back(1);
    buf1.push_back(2);
    buf1.push_back(3);
    buf1.push_back(4);
    buf1.push_back(5);
    buf1.push_back(6);

    ring_buffer<int, 4> buf2;

    buf2.push_back(10);
    buf2.push_back(20);
    buf2.push_back(30);
    buf2.push_back(40);
    buf2.push_back(50);
    buf2.push_back(60);

    std::swap(buf1, buf2);

    {
        std::vector<int> expected{30, 40, 50, 60};
        std::vector<int> actual;
        for (int& i : buf1) {
            actual.push_back(i);
        }
        assert(actual == expected);
    }

    {
        std::vector<int> expected{3, 4, 5, 6};
        std::vector<int> actual;
        for (int& i : buf2) {
            actual.push_back(i);
        }
        assert(actual == expected);
    }
}
