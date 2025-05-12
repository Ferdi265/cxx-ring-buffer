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

    auto it1 = buf1.begin();
    auto it2 = buf2.begin();
    std::swap(it1, it2);

    {
        assert(*it1 == 30);
        assert(*it2 == 3);
    }
}
