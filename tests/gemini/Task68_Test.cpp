#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<string, string> extractDcAndUsername(const string& inputString) {
    size_t atPos = inputString.find('@');
    if (atPos == string::npos) {
        return {"", ""};
    }
    string username = inputString.substr(0, atPos);
    string domain = inputString.substr(atPos + 1);

    vector<string> parts;
    size_t start = 0, pos;
    while ((pos = domain.find('.', start)) != string::npos) {
        parts.push_back(domain.substr(start, pos - start));
        start = pos + 1;
    }
    parts.push_back(domain.substr(start));

    string dc;
    for (size_t i = 0; i < parts.size(); i++) {
        dc += "dc=" + parts[i];
        if (i != parts.size() - 1) {
            dc += ",";
        }
    }

    return {username, dc};
}

bool test_extractDcAndUsername(const string& input, const string& expectedUser, const string& expectedDc) {
    auto [username, dc] = extractDcAndUsername(input);
    bool pass = (username == expectedUser && dc == expectedDc);
    cout << "Test input: " << input << "\n";
    if (pass) {
        cout << "PASS\n";
    } else {
        cout << "FAIL\n";
        cout << "  Expected username: " << expectedUser << ", Got: " << username << "\n";
        cout << "  Expected dc: " << expectedDc << ", Got: " << dc << "\n";
    }
    cout << "------------------------\n";
    return pass;
}

int main() {
    int passed = 0, failed = 0;

    vector<tuple<string, string, string>> testCases = {
        {"john@domain.com", "john", "dc=domain,dc=com"},
        {"alice@example.org", "alice", "dc=example,dc=org"},
        {"bob@sub.domain.co.uk", "bob", "dc=sub,dc=domain,dc=co,dc=uk"},
        {"invalidstring", "", ""},
        {"noatsign.com", "", ""}
    };

    for (auto& [input, expectedUser, expectedDc] : testCases) {
        if (test_extractDcAndUsername(input, expectedUser, expectedDc))
            passed++;
        else
            failed++;
    }

    cout << "Summary: Passed: " << passed << ", Failed: " << failed << endl;

    // LDAP search test (not implemented)
    cout << "\nLDAP search test: FAIL not implemented (requires LDAP server environment)\n";

    return 0;
}
