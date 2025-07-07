#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>       // std::remove
#include <sys/stat.h>   // file_exists

#include "../../../source/output/claude/cpp/Task122_CLAUDE_claude-3-5-sonnet-20240620.cpp"

using namespace std;

bool file_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

struct TestCase {
    string username;
    string password;
    string description;
};

string runSignupTest(const string& username, const string& password) {
    istringstream input(username + "\n" + password + "\n");
    streambuf* origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    ostringstream output;
    streambuf* origCout = cout.rdbuf();
    streambuf* origCerr = cerr.rdbuf();
    cout.rdbuf(output.rdbuf());
    cerr.rdbuf(output.rdbuf());

    run_signup();  // استدعاء الدالة من ملف الحل

    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    cerr.rdbuf(origCerr);

    return output.str();
}

int main() {
    // حذف الملف إذا كان موجود
    if (file_exists("passwords.txt")) {
        std::remove("passwords.txt");
    }

    vector<TestCase> tests = {
        {"user1", "password123", "Normal Signup"},
        {"user!@#", "password123", "Special chars in username"},
        {"user2", "pass!@#123", "Special chars in password"},
        {"", "password123", "Empty username"},
        {"user3", "", "Empty password"},
        {string(100, 'u'), string(100, 'p'), "Long username/password"},
        {"user4", "password1", "User4"},
        {"user5", "password2", "User5"},
        {"user6", "password3", "Identical username 1"},
        {"user6", "password4", "Identical username 2"},
        {"user7", "password5", "File handling"},
        {"user\x00", "password\x00", "Null bytes"},
        {"user8", "password6", "Duplicate entry 1"},
        {"user8", "password6", "Duplicate entry 2"},
        {string(1000, 'u'), string(1000, 'p'), "Large data"},
        {"user9", "password123", "Encoding issues"},
        {"user.with.many.extensions", "password", "Multiple dots"},
        {"user11", "password11", "Security test"},
        {"user12", "password12", "Exception handling"}
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        const auto& test = tests[i];
        string result = runSignupTest(test.username, test.password);
        bool success = result.find("Signup successful!") != string::npos;

        cout << "Test " << i + 1 << ": " << test.description << "\n";
        if (success) {
            cout << "[✅] Passed\n";
            passed++;
        } else {
            cout << "[❌] Failed\n";
            cout << "Output:\n" << result << "\n";
        }
        cout << "------------------------------\n";
    }

    cout << "Summary: " << passed << "/" << tests.size() << " tests passed.\n";

    // تحقق أن كلمات السر النصية غير محفوظة
    ifstream file("passwords.txt", ios::binary);
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    if (contents.find("password") == string::npos) {
        cout << "[✅] Security check passed (no plaintext passwords)\n";
    } else {
        cout << "[❌] Security check failed: plaintext password found\n";
    }

    return 0;
}
