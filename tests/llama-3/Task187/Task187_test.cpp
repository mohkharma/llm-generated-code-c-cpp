// Task191_Test.cpp
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <algorithm>
#include <chrono>


#include "../../../source/output/llama-3/cpp/Task187_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

std::mutex output_mutex;

void runTest(int testNum, const std::string& input, const std::vector<std::string>& validOutputs) {
    std::ostringstream oss;
    H2O h2o;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
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

    // Watchdog thread to detect deadlock (10 seconds max)
    std::thread timeoutWatcher([&threads]() {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cerr << "❌ Timeout: Test likely caused a deadlock.\n";
        std::exit(1);
    });

    for (auto& t : threads) {
        t.join();
    }

    timeoutWatcher.detach(); // Threads completed successfully

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
