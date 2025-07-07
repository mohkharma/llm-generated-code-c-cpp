#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "../../../source/output/llama-3/cpp/Task199_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

void assertEqual(const std::string& testName, const std::string& expected, const std::string& actual, int& passed, int& total) {
    total++;
    if (expected == actual) {
        std::cout << "✅ Passed: " << testName << "\n";
        passed++;
    } else {
        std::cout << "❌ Failed: " << testName << "\n";
        std::cout << "   Expected: " << expected << ", Got: " << actual << "\n";
    }
}

void assertTrue(const std::string& testName, bool condition, int& passed, int& total) {
    total++;
    if (condition) {
        std::cout << "✅ Passed: " << testName << "\n";
        passed++;
    } else {
        std::cout << "❌ Failed: " << testName << "\n";
    }
}

void assertFalse(const std::string& testName, bool condition, int& passed, int& total) {
    assertTrue(testName, !condition, passed, total);
}

std::string clockToString(const Clock& c) {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << (c.hours % 24) << ":"
        << std::setw(2) << std::setfill('0') << (c.minutes % 60);
    return oss.str();
}

int main() {
    int passed = 0, total = 0;

    // test_initial_time
    {
        Clock clock(10, 30);
        assertEqual("test_initial_time", "10:30", clockToString(clock), passed, total);
    }

    // test_add_minutes
    {
        Clock clock(10, 30);
        clock.addMinutes(60);
        assertEqual("test_add_minutes", "11:30", clockToString(clock), passed, total);
    }

    // test_subtract_minutes
    {
        Clock clock(10, 30);
        clock.subtractMinutes(90);
        assertEqual("test_subtract_minutes", "09:00", clockToString(clock), passed, total);
    }

    // test_add_overflow_minutes
    {
        Clock clock(23, 45);
        clock.addMinutes(30);
        assertEqual("test_add_overflow_minutes", "00:15", clockToString(clock), passed, total);
    }

    // test_subtract_underflow_minutes
    {
        Clock clock(0, 15);
        clock.subtractMinutes(30);
        assertEqual("test_subtract_underflow_minutes", "23:45", clockToString(clock), passed, total);
    }

    // test_equality_true
    {
        Clock clock1(10, 0);
        Clock clock2(10, 0);
        assertTrue("test_equality_true", clock1 == clock2, passed, total);
    }

    // test_equality_false
    {
        Clock clock1(10, 0);
        Clock clock2(9, 0);
        assertFalse("test_equality_false", clock1 == clock2, passed, total);
    }

    // test_midnight_edge_case
    {
        Clock clock(0, 0);
        assertEqual("test_midnight_edge_case", "00:00", clockToString(clock), passed, total);
    }

    // test_full_day_cycle
    {
        Clock clock(0, 0);
        clock.addMinutes(1440);
        assertEqual("test_full_day_cycle", "00:00", clockToString(clock), passed, total);
    }

    // test_negative_overflow
    {
        Clock clock(1, 0);
        clock.subtractMinutes(1440);
        assertEqual("test_negative_overflow", "01:00", clockToString(clock), passed, total);
    }

    std::cout << "\n📊 Summary: " << passed << "/" << total << " tests passed.\n";

    return 0;
}
