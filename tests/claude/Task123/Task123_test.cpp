#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>
#include <algorithm>
#include "../../../source/output/claude/cpp/Task123_CLAUDE_claude-3-5-sonnet-20240620.cpp"

using namespace std;
using namespace std::chrono;

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

void test_create_session_valid_user_id() {
    SessionManager sm;
    string user_id = "user123";
    string session_id = sm.createSession(user_id);
    Session* session = sm.getSession(session_id);
    assert_true(session != nullptr, "test_create_session_valid_user_id");
    assert_true(session->userId == user_id, "session has correct userId");
}

void test_create_session_unique_session_id() {
    SessionManager sm;
    string user_id = "user123";
    string s1 = sm.createSession(user_id);
    string s2 = sm.createSession(user_id);
    assert_true(s1 != s2, "test_create_session_unique_session_id");
}

void test_get_session_valid_session() {
    SessionManager sm;
    string user_id = "user123";
    string sid = sm.createSession(user_id);
    Session* session = sm.getSession(sid);
    assert_true(session != nullptr, "test_get_session_valid_session: not null");
    assert_true(session->userId == user_id, "test_get_session_valid_session: userId match");
}

void test_get_session_expired() {
    SessionManager sm(1);  // 1 second timeout
    string sid = sm.createSession("user123");
    this_thread::sleep_for(chrono::seconds(2));
    Session* session = sm.getSession(sid);
    assert_true(session == nullptr, "test_get_session_expired");
}

void test_destroy_session() {
    SessionManager sm;
    string sid = sm.createSession("user123");
    sm.destroySession(sid);
    Session* session = sm.getSession(sid);
    assert_true(session == nullptr, "test_destroy_session");
}

void test_destroy_nonexistent_session() {
    SessionManager sm;
    sm.destroySession("fake-session-id");  // should not crash
    assert_true(true, "test_destroy_nonexistent_session");
}

void test_cleanup_expired_sessions() {
    SessionManager sm(1);  // timeout = 1s
    string id1 = sm.createSession("user123");
    string id2 = sm.createSession("user456");
    this_thread::sleep_for(chrono::seconds(2));
    sm.cleanupExpiredSessions();
    assert_true(sm.getSession(id1) == nullptr && sm.getSession(id2) == nullptr,
                "test_cleanup_expired_sessions");
}

void test_get_session_updates_last_activity() {
    SessionManager sm;
    string sid = sm.createSession("user123");
    Session* session = sm.getSession(sid);
    auto first = session->lastActivity;

    this_thread::sleep_for(chrono::milliseconds(1200));

    session = sm.getSession(sid); // هذا التحديث سيعدل lastActivity
    auto updated = session->lastActivity;

    auto diff = chrono::duration_cast<chrono::milliseconds>(updated - first).count();
    assert_true(diff >= 1000, "test_get_session_updates_last_activity");
}

void test_create_session_session_id_format() {
    SessionManager sm;
    string sid = sm.createSession("user123");
    bool is_uuid_like = count(sid.begin(), sid.end(), '-') == 4 && sid.size() >= 36;
    assert_true(is_uuid_like, "test_create_session_session_id_format");
}

void test_no_sessions_after_cleanup() {
    SessionManager sm(1);  // 1 second timeout
    string sid = sm.createSession("user123");
    this_thread::sleep_for(chrono::seconds(2));
    sm.cleanupExpiredSessions();
    assert_true(sm.getSession(sid) == nullptr, "test_no_sessions_after_cleanup");
}

int main() {
    test_create_session_valid_user_id();
    test_create_session_unique_session_id();
    test_get_session_valid_session();
    test_get_session_expired();
    test_destroy_session();
    test_destroy_nonexistent_session();
    test_cleanup_expired_sessions();
    test_get_session_updates_last_activity();
    test_create_session_session_id_format();
    test_no_sessions_after_cleanup();

    cout << "\nTests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    if (failed == 0)
        cout << "✅ All tests passed." << endl;
    else
        cout << "❌ Some tests failed." << endl;

    return failed;
}
