 #include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <functional>

#include "../../../source/output/llama-3/cpp/Task188_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

std::string runTest(int n, const std::string& expected) {
    std::ostringstream output;
    FooBar fooBar(n);

    auto printFoo = [&output]() { output << "foo"; };
    auto printBar = [&output]() { output << "bar"; };

    std::thread t1(&FooBar::foo, &fooBar, printFoo);
    std::thread t2(&FooBar::bar, &fooBar, printBar);

    t1.join();
    t2.join();

    std::string result = output.str();
    if (result == expected) {
        return "✅ Test passed";
    } else {
        return "❌ Test failed\nExpected: " + expected + "\nGot:      " + result;
    }
}

int main() {
    bool allPassed = true;

    struct TestCase {
        int n;
        std::string expected;
    };

    TestCase testCases[] = {
        {1, "foobar"},
        {2, "foobarfoobar"},
        {3, "foobarfoobarfoobar"}
    };

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
