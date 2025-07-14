#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Record {
    string key;
    string value;
};

bool compareRecords(const Record& a, const Record& b) {
    return a.key < b.key;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

vector<Record> readFile(const string &filename) {
    vector<Record> records;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return records;
    }

    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            Record record;
            record.key = trim(line.substr(0, pos));
            record.value = trim(line.substr(pos + 1));
            records.push_back(record);
        } else {
            cerr << "Warning: Skipping invalid line: " << line << endl;
        }
    }

    file.close();
    return records;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    vector<Record> records = readFile(filename);
    sort(records.begin(), records.end(), compareRecords);

    for (const auto &record : records) {
        cout << record.key << ": " << record.value << endl;
    }

    return 0;
}

/*
 *to Run this Task File: =>
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test /home/kali/CLionProjects/llm-generated-code-cpp/tests/testFile.txt
 */
