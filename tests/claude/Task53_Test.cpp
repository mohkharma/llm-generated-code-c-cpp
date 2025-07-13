#include "../../source/output/claude/cpp/Task53_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class Session;
using namespace std;

static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT_TRUE(cond) \
    if (!(cond)) { \
        cout << "FAILED: " #cond << " at line " << __LINE__ << endl; \
        tests_failed++; \
    } else { \
        tests_passed++; \
    }

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))
#define ASSERT_EQ(val1, val2) ASSERT_TRUE((val1) == (val2))
#define ASSERT_NE(val1, val2) ASSERT_TRUE((val1) != (val2))
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE((ptr) != nullptr)
#define ASSERT_NULL(ptr) ASSERT_TRUE((ptr) == nullptr)
#define ASSERT_GT(val1, val2) ASSERT_TRUE((val1) > (val2))

void test_create_session() {
    SessionManager sm;
    string user_id = "user123";
    string sid = sm.createSession(user_id);

    ASSERT_TRUE(!sid.empty());
    ASSERT_NOT_NULL(sm.getSession(sid));

    Session* sess = sm.getSession(sid);
    ASSERT_NOT_NULL(sess);
    ASSERT_EQ(sess->userId, user_id);
    ASSERT_TRUE(!sess->sessionId.empty());
}

void test_get_session() {
    SessionManager sm;
    string user_id = "user123";
    string sid = sm.createSession(user_id);

    Session* sess = sm.getSession(sid);
    ASSERT_NOT_NULL(sess);
    ASSERT_EQ(sess->userId, user_id);
}

void test_get_invalid_session() {
    SessionManager sm;
    string invalid_sid = "00000000-0000-0000-0000-000000000000";
    Session* sess = sm.getSession(invalid_sid);
    ASSERT_NULL(sess);
}

void test_session_timeout() {
    SessionManager sm(1); // 1 second timeout
    string user_id = "user123";
    string sid = sm.createSession(user_id);

    this_thread::sleep_for(chrono::seconds(2));
    Session* sess = sm.getSession(sid);
    ASSERT_NULL(sess);
}

void test_destroy_session() {
    SessionManager sm;
    string user_id = "user123";
    string sid = sm.createSession(user_id);

    sm.destroySession(sid);
    ASSERT_TRUE(sm.getSession(sid) == nullptr);
}

void test_cleanup_expired_sessions() {
    SessionManager sm(1); // 1 second timeout
    string sid1 = sm.createSession("user123");
    string sid2 = sm.createSession("user456");

    this_thread::sleep_for(chrono::seconds(2));
    sm.cleanupExpiredSessions();

    ASSERT_TRUE(sm.getSession(sid1) == nullptr);
    ASSERT_NOT_NULL(sm.getSession(sid2));
}

void test_cleanup_no_expired_sessions() {
    SessionManager sm;
    string sid1 = sm.createSession("user123");
    string sid2 = sm.createSession("user789");

    sm.cleanupExpiredSessions();

    ASSERT_NOT_NULL(sm.getSession(sid1));
    ASSERT_NOT_NULL(sm.getSession(sid2));
}

void test_update_last_accessed() {
    SessionManager sm;
    string user_id = "user123";
    string sid = sm.createSession(user_id);

    Session* sess1 = sm.getSession(sid);
    ASSERT_NOT_NULL(sess1);

    time_t old_accessed = sess1->lastAccessed;
    this_thread::sleep_for(chrono::seconds(1));

    Session* sess2 = sm.getSession(sid);
    ASSERT_NOT_NULL(sess2);

    ASSERT_GT(sess2->lastAccessed, old_accessed);
}

void test_create_multiple_sessions() {
    SessionManager sm;
    string sid1 = sm.createSession("user123");
    string sid2 = sm.createSession("user456");

    ASSERT_NOT_NULL(sm.getSession(sid1));
    ASSERT_NOT_NULL(sm.getSession(sid2));
    ASSERT_NE(sid1, sid2);
}

void test_destroy_non_existent_session() {
    SessionManager sm;
    string non_existent_sid = "ffffffff-ffff-ffff-ffff-ffffffffffff";

    sm.destroySession(non_existent_sid); // لا يجب أن يرمي خطأ
    ASSERT_TRUE(sm.getSession(non_existent_sid) == nullptr);
}

int main() {
    cout << "Running SessionManager tests...\n";

    test_create_session();
    test_get_session();
    test_get_invalid_session();
    test_session_timeout();
    test_destroy_session();
    test_cleanup_expired_sessions();
    test_cleanup_no_expired_sessions();
    test_update_last_accessed();
    test_create_multiple_sessions();
    test_destroy_non_existent_session();

    cout << "Tests passed: " << tests_passed << endl;
    cout << "Tests failed: " << tests_failed << endl;

    if (tests_failed > 0) {
        cout << "Some tests failed." << endl;
        return 1;
    } else {
        cout << "All tests passed." << endl;
        return 0;
    }
}
