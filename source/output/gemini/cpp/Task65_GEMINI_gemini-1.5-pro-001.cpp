#include <iostream>
#include <fstream>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename);
    string content;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();
        return content;
    } else {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        return "";
    }
}
