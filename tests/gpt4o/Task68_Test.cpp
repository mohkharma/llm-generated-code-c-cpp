#include <iostream>
#include <string>
#include <vector>

using namespace std;

// دالة تفصل username و domain component من سلسلة user@domain.com
bool parseInput(const string& input, string& domainComponent, string& username) {
    size_t atPos = input.find('@');
    if (atPos == string::npos) {
        domainComponent = "";
        username = "";
        return false;
    }
    username = input.substr(0, atPos);
    domainComponent = input.substr(atPos + 1);
    return true;
}

bool test_parseInput(const string& input, const string& expectedDomain, const string& expectedUser) {
    string domain, user;
    bool success = parseInput(input, domain, user);
    bool pass = (domain == expectedDomain) && (user == expectedUser);
    cout << "Test input: " << input << endl;
    if (pass) {
        cout << "PASS\n";
    } else {
        cout << "FAIL\n";
        cout << "  Expected domainComponent: " << expectedDomain << ", Got: " << domain << endl;
        cout << "  Expected username: " << expectedUser << ", Got: " << user << endl;
    }
    cout << "----------------------\n";
    return pass;
}

int main() {
    vector<tuple<string, string, string>> testCases = {
        {"john@domain.com", "domain.com", "john"},
        {"alice@example.org", "example.org", "alice"},
        {"bob@sub.domain.co.uk", "sub.domain.co.uk", "bob"},
        {"invalidstring", "", ""},
        {"noatsign.com", "", ""}
    };

    int passed = 0, failed = 0;
    for (auto& [input, expectedDomain, expectedUser] : testCases) {
        if (test_parseInput(input, expectedDomain, expectedUser))
            passed++;
        else
            failed++;
    }

    cout << "Summary: Passed: " << passed << ", Failed: " << failed << endl;

    // بالنسبة لاختبار LDAP search (حقيقي) غير ممكن هنا بدون سيرفر LDAP
    cout << "\nLDAP search test: FAIL not implemented (requires LDAP server environment)" << endl;

    return 0;
}
