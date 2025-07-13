#include <iostream>
#include <cassert>
#include "../../../source/output/gemini/cpp/Task123_GEMINI_gemini-1.5-pro-001.cpp"

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

void test_create_session() {
    SessionManager sm;
    string session_id = sm.createSession("user1");
    assert_true(!session_id.empty(), "test_create_session: session_id not empty");

    Session* session = sm.getSession(session_id);
    assert_true(session != nullptr, "test_create_session: session exists");
    assert_true(session->username == "user1", "test_create_session: username correct");
    assert_true(session->isValid(), "test_create_session: session is valid");
}

void test_get_invalid_session() {
    SessionManager sm;
    Session* session = sm.getSession("invalid_id");
    assert_true(session == nullptr, "test_get_invalid_session returns nullptr");
}

void test_delete_session() {
    SessionManager sm;
    string session_id = sm.createSession("user2");
    sm.deleteSession(session_id);
    Session* session = sm.getSession(session_id);
    assert_true(session == nullptr, "test_delete_session: session deleted");
}

void test_multiple_sessions_unique_ids() {
    SessionManager sm;
    string id1 = sm.createSession("userA");
    string id2 = sm.createSession("userB");

    assert_true(id1 != id2, "test_multiple_sessions_unique_ids");
}

void test_reuse_deleted_session_id() {
    SessionManager sm;
    string id = sm.createSession("userX");
    sm.deleteSession(id);
    string new_id = sm.createSession("userX");
    assert_true(new_id == "session_userX", "test_reuse_deleted_session_id: same ID reused");
}

int main() {
    test_create_session();
    test_get_invalid_session();
    test_delete_session();
    test_multiple_sessions_unique_ids();
    test_reuse_deleted_session_id();

    cout << "\nTests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    if (failed == 0)
        cout << "✅ All tests passed." << endl;
    else
        cout << "❌ Some tests failed." << endl;

    return failed;
}
