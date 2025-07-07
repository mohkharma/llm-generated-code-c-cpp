 #include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <functional>

#include "../../../source/output/gpt4o/cpp/Task189_OPENAI_gpt-4o.cpp"

std::string runTest(int n, const std::string& expected) {
    std::ostringstream output;
    ZeroEvenOdd zeo(n);

    auto printNumber = [&output](int x) {
        output << x;
    };

    std::thread t1(&ZeroEvenOdd::zero, &zeo, printNumber);
    std::thread t2(&ZeroEvenOdd::even, &zeo, printNumber);
    std::thread t3(&ZeroEvenOdd::odd, &zeo, printNumber);

    t1.join();
    t2.join();
    t3.join();

    std::string result = output.str();
    if (result == expected) {
        return "✅ Test passed";
    } else {
        return "❌ Test failed\nExpected: " + expected + "\nGot:      " + result;
    }
}

int main() {
    struct TestCase {
        int n;
        std::string expected;
    };

    TestCase testCases[] = {
        {2, "0102"},
        {5, "0102030405"}
    };

    bool allPassed = true;

    for (int i = 0; i < sizeof(testCases) / sizeof(TestCase); ++i) {
        std::cout << "Running Test Case " << i + 1 << "...\n";
        std::string result = runTest(testCases[i].n, testCases[i].expected);
        std::cout << result << "\n\n";

        if (result.find("❌") != std::string::npos) {
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "🎉 All test cases passed successfully.\n";
    } else {
        std::cout << "❗ Some test cases failed.\n";
    }

    return 0;
}
