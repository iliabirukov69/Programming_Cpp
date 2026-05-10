#include "functions.hpp"
#include <iostream>

int main() {
    std::cout << "=== Task 1 ===" << std::endl;
    solveTask1("input.txt", "output_task1.txt", 2000);
    std::cout << "Task 1 completed. Check output_task1.txt" << std::endl;

    std::cout << "\n=== Task 2 ===" << std::endl;
    std::string testText = "level hello world madam test";
    std::vector<std::string> result2 = processTask2(testText);
    for (const auto& w : result2) {
        std::cout << w << std::endl;
    }

    std::cout << "\n=== Task 3 ===" << std::endl;
    solveTask3("input.txt", "output.txt");
    std::cout << "Task 3 completed. Check output.txt" << std::endl;

    return 0;
}
