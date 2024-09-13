#include <iostream>
#include <vector>
#include <chrono>

int main() {
    const size_t iterations = 100000000;
    std::vector<size_t> vec;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        vec.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "C++ std::vector time: " << duration.count() << " seconds\n";

    return 0;
}
