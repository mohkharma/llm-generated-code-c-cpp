// Task188_Test.cpp
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <algorithm>

#include "../../../source/output/gpt4o/cpp/Task187_OPENAI_gpt-4o.cpp"

std::mutex output_mutex;

void runTest(int testNum, const std::string& input, const std::vector<std::string>& validOutputs) {
    std::ostringstream oss;
    H2O h2o;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];  // نسخة منفصلة لكل thread
        if (c == 'H') {
            threads.emplace_back([&, c]() {
                h2o.hydrogen([&]() {
                    std::lock_guard<std::mutex> lock(output_mutex);
                    oss << 'H';
                });
            });
        } else if (c == 'O') {
            threads.emplace_back([&, c]() {
                h2o.oxygen([&]() {
                    std::lock_guard<std::mutex> lock(output_mutex);
                    oss << 'O';
                });
            });
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    std::string result = oss.str();
    bool passed = false;
    for (const std::string& expected : validOutputs) {
        if (result == expected) {
            passed = true;
            break;
        }
    }

    if (passed) {
        std::cout << "✅ Test Case " << testNum << " Passed: " << result << "\n";
    } else {
        std::cout << "❌ Test Case " << testNum << " Failed\n";
        std::cout << "   Output:   " << result << "\n";
        std::cout << "   Expected one of:\n";
        for (const std::string& expected : validOutputs) {
            std::cout << "     - " << expected << "\n";
        }
    }
}

int main() {
    runTest(1, "HOH", {"HHO", "HOH", "OHH"});
    runTest(2, "OOHHHH", {
        "HHOHHO", "HOHHHO", "OHHHHO", "HHOHOH",
        "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH", "OHHOHH"
    });

    return 0;
}
