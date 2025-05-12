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
        auto it = buf.begin();
        ++it;
        it++;
        assert(*it == 5);
        --it;
        it--;
        assert(*it == 3);
    }
}
