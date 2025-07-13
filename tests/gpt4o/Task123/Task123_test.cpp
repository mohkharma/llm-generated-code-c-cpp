#include <iostream>
#include <thread>
#include <cassert>
#include "../../../source/output/gpt4o/cpp/Task123_OPENAI_gpt-4o.cpp"  // تأكد من المسار

using namespace std;

int passed = 0, failed = 0;

void assert_true(bool condition, const string& test_name) {
    if (condition) {
        cout << "[✔] " << test_name << endl;
        passed++;
    } else {
        cout << "[✘] " << test_name << endl;
        failed++;
    }
}

void test_get_user_id() {
    UserSession session("user42");
    assert_true(session.getUserId() == "user42", "test_get_user_id");
}

void test_duration_starts_near_zero() {
    UserSession session("user1");
    double d = session.getDuration();
    assert_true(d >= 0.0 && d < 0.1, "test_duration_starts_near_zero");
}

void test_duration_increases_over_time() {
    UserSession session("user1");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    double d = session.getDuration();
    assert_true(d >= 0.5, "test_duration_increases_over_time");
}

void test_independent_sessions_have_different_start_times() {
    UserSession s1("a");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    UserSession s2("b");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    double d1 = s1.getDuration();
    double d2 = s2.getDuration();
    assert_true(d1 > d2, "test_independent_sessions_have_different_start_times");
}

int main() {
    test_get_user_id();
    test_duration_starts_near_zero();
    test_duration_increases_over_time();
    test_independent_sessions_have_different_start_times();

    cout << "\nTests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    if (failed == 0)
        cout << "✅ All tests passed." << endl;
    else
        cout << "❌ Some tests failed." << endl;

    return failed;
}
