#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

 #include "../../../source/output/gemini/cpp/Task121_GEMINI_gemini-1.5-pro-001.cpp"

string runTest(const string& filepath) {
    istringstream input(filepath + "\n");
    streambuf* origCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    ostringstream output;
    streambuf* origCout = cout.rdbuf();
    streambuf* origCerr = cerr.rdbuf();
    cout.rdbuf(output.rdbuf());
    cerr.rdbuf(output.rdbuf());

    run_upload_program();

    cin.rdbuf(origCin);
    cout.rdbuf(origCout);
    cerr.rdbuf(origCerr);

    return output.str();
}

int main() {
    vector<string> testFiles = {
        "testFiles/sample.txt",
        "testFiles/missing.txt",
        "testFiles/empty.txt"
    };

    int passed = 0;
    for (const string& file : testFiles) {
        cout << "Running test: " << file << endl;

        string actual = runTest(file);
        string expected;

        if (fs::exists(file)) {
            expected = "Enter the path to the file you want to upload: File uploaded successfully!\n";
        } else {
            expected = "Enter the path to the file you want to upload: Error opening file: " + file + "\n";
        }

        if (actual == expected) {
            cout << "[✅] Passed\n";
            passed++;
        } else {
            cout << "[❌] Failed\n";
            cout << "Expected:\n" << expected;
            cout << "Got:\n" << actual;
        }

        cout << "-----------------------------\n";
    }

    cout << "Summary: " << passed << "/" << testFiles.size() << " tests passed.\n";
    return 0;
}
