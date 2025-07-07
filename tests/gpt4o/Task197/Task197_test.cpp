#include <iostream>
#include <cmath>
#include <string>
#include <utility>
#include "../../../source/output/gpt4o/cpp/Task197_OPENAI_gpt-4o.cpp"
#include <vector>

using namespace std;

bool assertInCircle(double x, double y, double radius, double cx, double cy) {
    double dx = x - cx;
    double dy = y - cy;
    return dx * dx + dy * dy <= radius * radius + 1e-9;
}

bool assertExact(double x, double expected) {
    return fabs(x - expected) < 1e-9;
}

bool runTest(const string& testName, double radius, double cx, double cy, int repetitions) {
    Solution sol(radius, cx, cy);
    bool passed = true;
    for (int i = 0; i < repetitions; ++i) {
        pair<double, double> point = sol.randPoint();
        if (radius == 0.0) {
            if (!assertExact(point.first, cx) || !assertExact(point.second, cy)) {
                passed = false;
                break;
            }
        } else {
            if (!assertInCircle(point.first, point.second, radius, cx, cy)) {
                passed = false;
                break;
            }
        }
    }

    cout << "Test " << testName << ": "
         << (passed ? "✅ Passed" : "❌ Failed") << endl;
    return passed;
}

int main() {
    int passed = 0, total = 0;

    struct TestCase {
        string name;
        double radius, cx, cy;
    };

    vector<TestCase> tests = {
        {"UnitCircle", 1.0, 0.0, 0.0},
        {"OffsetCenter", 1.0, 1.0, 1.0},
        {"LargeRadius", 100.0, 0.0, 0.0},
        {"SmallRadius", 0.1, 0.0, 0.0},
        {"NegativeCenter", 1.0, -5.0, -5.0},
        {"LargeCenter", 1.0, 1e6, 1e6},
        {"ZeroRadius", 0.0, 0.0, 0.0},
        {"HugeRadius", 1e8, 0.0, 0.0},
        {"NonZeroCenter", 10.0, 10.0, 10.0},
        {"MultipleCalls", 50.0, 0.0, 0.0}
    };

    for (const auto& test : tests) {
        total++;
        if (runTest(test.name, test.radius, test.cx, test.cy, 100)) {
            passed++;
        }
    }

    cout << "\n✅ Summary: " << passed << " / " << total << " tests passed.\n";
    return 0;
}
