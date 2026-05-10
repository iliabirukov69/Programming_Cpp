#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "functions.hpp"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int N;
    std::cout << "Write N[1-19]: ";
    std::cin >> N;

    if (N < 1 || N > 19) {
        std::cout << "Faile" << std::endl;
        return 1;
    }

    std::cout << "Factorial: " << N << " = " << factorial(N) << std::endl;
    std::cout << std::endl;

    std::vector<int> data(10000);
    for (int i = 0; i < 10000; i++) {
        data[i] = rand() % 10000;
    }

    std::vector<int> dataQuick = data;
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(dataQuick, 0, static_cast<int>(dataQuick.size()) - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationQuick = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::vector<int> dataBubble = data;
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(dataBubble);
    end = std::chrono::high_resolution_clock::now();
    auto durationBubble = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Fast sorted " << durationQuick.count() << " s" << std::endl;
    std::cout << "Sort by exchanges: " << durationBubble.count() << " s" << std::endl;
    std::cout << std::endl;
    std::cout << "Quick sort is faster in " << durationBubble.count() / durationQuick.count() << " " << std::endl;

    return 0;
}
