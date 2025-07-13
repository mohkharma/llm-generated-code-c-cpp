#include <iostream>
#include <thread>
#include <sstream>

#include "../../../source/output/gemini/cpp/Task196_GEMINI_gemini-1.5-pro-001.cpp"

using namespace std;

bool runTest(int n, const string& expected, const string& testName) {
    stringstream output;
    auto printNumber = [&output](int x) {
        output << x;
    };

    ZeroEvenOdd zeo(n);

    thread t1(&ZeroEvenOdd::zero, &zeo, printNumber);
    thread t2(&ZeroEvenOdd::even, &zeo, printNumber);
    thread t3(&ZeroEvenOdd::odd, &zeo, printNumber);

    t1.join();
    t2.join();
    t3.join();

    string result = output.str();
    bool passed = (result == expected);

    cout << "Test " << testName << ": "
         << (passed ? "✅ Passed" : "❌ Failed")
         << " | Output: \"" << result << "\""
         << " | Expected: \"" << expected << "\"\n";

    return passed;
}

int main() {
    int passed = 0, total = 0;

    struct TestCase {
        int n;
        string expected;
    };

    vector<TestCase> tests = {
        {1, "01"},
        {2, "0102"},
        {3, "010203"},
        {4, "01020304"},
        {5, "0102030405"},
        {6, "010203040506"},
        {7, "01020304050607"},
        {8, "0102030405060708"},
        {9, "010203040506070809"},
        {10, "01020304050607080910"}
    };

    for (size_t i = 0; i < tests.size(); ++i) {
        total++;
        if (runTest(tests[i].n, tests[i].expected, "Case " + to_string(i + 1))) {
            passed++;
        }
    }

    cout << "\n✅ Summary: " << passed << " / " << total << " tests passed.\n";
    return 0;
}
