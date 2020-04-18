#include <iostream>
#include <ring-buffer.h>

int main() {
    ring_buffer<int, 4> buf;

    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    buf.push_back(5);
    buf.push_back(6);

    std::cout << "before\n";
    for (int& i : buf) {
        std::cout << i << "\n";
    }

    buf.push_back(7);

    std::cout << "after\n";
    for (int& i : buf) {
        std::cout << i << "\n";
    }
}
