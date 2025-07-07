 #include <iostream>
#include <sstream>
#include <thread>
#include <string>
#include <streambuf>

#include "../../../source/output/gemini/cpp/Task188_GEMINI_gemini-1.5-pro-001.cpp"

std::string captureOutput(int n) {
    std::ostringstream captured;
    std::streambuf* oldCout = std::cout.rdbuf(captured.rdbuf()); // Redirect cout

    FooBar fooBar(n);
    std::thread t1(&FooBar::foo, &fooBar);
    std::thread t2(&FooBar::bar, &fooBar);
    t1.join();
    t2.join();

    std::cout.rdbuf(oldCout); // Restore original cout
    return captured.str();
}

int main() {
    struct TestCase {
        int n;
        std::string expected;
    };

    TestCase testCases[] = {
        {1, "foobar"},
        {2, "foobarfoobar"},
        {3, "foobarfoobarfoobar"}
    };

    bool allPassed = true;
    for (int i = 0; i < sizeof(testCases) / sizeof(TestCase); ++i) {
        std::cout << "Running Test Case " << i + 1 << "...\n";
        std::string result = captureOutput(testCases[i].n);

        if (result == testCases[i].expected) {
            std::cout << "✅ Test passed\n\n";
        } else {
            std::cout << "❌ Test failed\nExpected: " << testCases[i].expected
                      << "\nGot:      " << result << "\n\n";
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
