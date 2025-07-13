// Task999_MANUAL_simple_session_Test.cpp

#include <iostream>
#include <sstream>
#include <cassert>
#include "../../../source/output/codestral/cpp/Task123_MISTRAL_codestral-latest.cpp"


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

void test_create_session_sets_user_id_and_active() {
    Session s(42);
    assert_true(s.getUserId() == 42, "test_create_session_sets_user_id");
    assert_true(s.getIsActive() == true, "test_create_session_sets_active_true");
}

void test_end_session_sets_inactive() {
    Session s(99);
    s.endSession();
    assert_true(s.getIsActive() == false, "test_end_session_sets_inactive");
}

void test_multiple_sessions_independent() {
    Session s1(1);
    Session s2(2);
    s1.endSession();
    assert_true(s1.getIsActive() == false, "test_multiple_sessions_s1_inactive");
    assert_true(s2.getIsActive() == true, "test_multiple_sessions_s2_still_active");
    assert_true(s1.getUserId() == 1 && s2.getUserId() == 2, "test_multiple_sessions_correct_user_ids");
}

void test_end_session_multiple_times() {
    Session s(123);
    s.endSession();
    s.endSession(); // no crash
    assert_true(s.getIsActive() == false, "test_end_session_multiple_times");
}

int main() {
    test_create_session_sets_user_id_and_active();
    test_end_session_sets_inactive();
    test_multiple_sessions_independent();
    test_end_session_multiple_times();

    cout << "\nTests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    if (failed == 0)
        cout << "✅ All tests passed." << endl;
    else
        cout << "❌ Some tests failed." << endl;

    return failed;
}