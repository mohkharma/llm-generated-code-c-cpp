#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// دالة مساعدة لقص الفراغات من البداية والنهاية
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == string::npos || end == string::npos) {
        return "";
    }
    return s.substr(start, end - start + 1);
}

int main() {
    // البيانات كما في التيست كيس داخل string
    string test_data =
        "zoo : value1\n"
        "book : value2\n"
        "door : value3\n"
        "tree : value4\n";

    istringstream file(test_data);
    string line;
    vector<pair<string, string>> records;

    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string key = trim(line.substr(0, pos));
            string value = trim(line.substr(pos + 1));
            records.push_back(make_pair(key, value));
        } else {
            cerr << "Warning: skipping invalid line: " << line << endl;
        }
    }

    // ترتيب السجلات حسب المفتاح
    sort(records.begin(), records.end(),
         [](const pair<string,string>& a, const pair<string,string>& b) {
            return a.first < b.first;
         });

    // طباعة النتيجة
    for (const auto& record : records) {
        cout << record.first << ": " << record.second << endl;
    }

    return 0;
}
