#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct KeyValuePair {
    string key;
    string value;
};

bool compareByKey(const KeyValuePair& a, const KeyValuePair& b) {
    return a.key < b.key;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    string filePath = argv[1];
    vector<KeyValuePair> keyValuePairs;

    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            KeyValuePair pair;
            pair.key = trim(line.substr(0, pos));
            pair.value = trim(line.substr(pos + 1));
            keyValuePairs.push_back(pair);
        } else {
            cerr << "Warning: skipping invalid line: " << line << endl;
        }
    }
    inputFile.close();

    sort(keyValuePairs.begin(), keyValuePairs.end(), compareByKey);

    for (const auto& pair : keyValuePairs) {
        cout << pair.key << ": " << pair.value << endl;
    }

    return 0;
}
/*
 *to Run this file: =>
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test /home/kali/CLionProjects/llm-generated-code-cpp/tests/testFile.txt
 */