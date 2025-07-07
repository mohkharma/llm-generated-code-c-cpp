#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "../../../source/output/gpt4o/cpp/Task198_OPENAI_gpt-4o.cpp"

bool inRange(int x, int low, int high) {
    return x >= low && x <= high;
}

int main() {
    srand((unsigned)time(0));  // Initialize rand() only once

    int totalPassed = 0;
    int totalTests = 10;

    // 1. Uniform distribution test
    {
        std::map<int, int> counts;
        int n = 100000;
        for (int i = 0; i < n; i++) {
            counts[rand10()]++;
        }
        bool uniform = true;
        for (int i = 1; i <= 10; i++) {
            if (counts[i] < n / 15 || counts[i] > n / 7) {
                uniform = false;
                break;
            }
        }
        if (uniform) {
            std::cout << "✅ Passed: Uniform distribution\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: Uniform distribution not within expected range\n";
        }
    }

    // 2. Single call coverage
    {
        std::set<int> results;
        for (int i = 0; i < 100; i++) {
            results.insert(rand10());
        }
        bool allPresent = true;
        for (int i = 1; i <= 10; i++) {
            if (results.find(i) == results.end()) {
                allPresent = false;
                break;
            }
        }
        if (allPresent) {
            std::cout << "✅ Passed: Single call range coverage\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: Not all values [1-10] found in multiple rand10() calls\n";
        }
    }

    // 3. Multiple calls within bounds
    {
        bool valid = true;
        for (int i = 0; i < 10; i++) {
            int r = rand10();
            if (!inRange(r, 1, 10)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << "✅ Passed: Multiple calls within range\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: rand10() returned value out of [1,10]\n";
        }
    }

    // 4. Performance test
    {
        std::cout << "▶️ Running Performance Test...\n";
        int n = 100000;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            rand10();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (durationMs < 2000) {
            std::cout << "✅ Passed: Performance (" << durationMs << " ms)\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: Performance too slow (" << durationMs << " ms)\n";
        }
    }

    // 5. Consistency test
    {
        bool consistent = true;
        for (int i = 0; i < 100; i++) {
            int r = rand10();
            if (!inRange(r, 1, 10)) {
                consistent = false;
                break;
            }
        }
        if (consistent) {
            std::cout << "✅ Passed: Consistency\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: Inconsistent rand10() output\n";
        }
    }

    // 6. Boundary check
    {
        bool valid = true;
        for (int i = 0; i < 1000; i++) {
            int r = rand10();
            if (!inRange(r, 1, 10)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << "✅ Passed: Boundary conditions\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: rand10() produced value outside [1, 10]\n";
        }
    }

    // 7. Randomness diversity
    {
        std::set<int> values;
        for (int i = 0; i < 1000; i++) {
            values.insert(rand10());
        }
        if (values.size() == 10) {
            std::cout << "✅ Passed: Randomness - all values present\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: Randomness - not all values [1-10] seen\n";
        }
    }

    // 8. Extreme values presence
    {
        bool found1 = false, found10 = false;
        for (int i = 0; i < 1000; i++) {
            int r = rand10();
            if (r == 1) found1 = true;
            if (r == 10) found10 = true;
        }
        if (found1 && found10) {
            std::cout << "✅ Passed: Edge value presence (1 and 10)\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: rand10() did not produce both 1 and 10\n";
        }
    }

    // 9. Multiple executions consistency
    {
        bool consistent = true;
        for (int i = 0; i < 100; i++) {
            int r = rand10();
            if (!inRange(r, 1, 10)) {
                consistent = false;
                break;
            }
        }
        if (consistent) {
            std::cout << "✅ Passed: Multiple executions\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: rand10() inconsistency in repeated execution\n";
        }
    }

    // 10. Edge case repeated
    {
        std::set<int> edges;
        for (int i = 0; i < 10000; i++) {
            int r = rand10();
            if (r == 1 || r == 10) edges.insert(r);
        }
        if (edges.count(1) && edges.count(10)) {
            std::cout << "✅ Passed: Edge case check\n";
            totalPassed++;
        } else {
            std::cout << "❌ Failed: rand10() did not return both edges (1 and 10)\n";
        }
    }

    std::cout << "\n📊 Summary: " << totalPassed << "/" << totalTests << " tests passed.\n";

    return 0;
}
