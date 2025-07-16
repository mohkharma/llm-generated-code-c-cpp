#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int upload_file_by_path(const string& filePath) {
    ifstream file(filePath, ios::binary);

    if (file.is_open()) {
        // Get the file size
        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);

        // Read the file content into a buffer
        char* buffer = new char[fileSize];
        file.read(buffer, fileSize);
        file.close();

        // Process the uploaded file content (buffer) here
        // ...

        delete[] buffer;

        cout << "File '" << filePath << "' uploaded successfully!" << endl;
        cout << "Test case for '" << filePath << "': PASS" << endl;
        return 0;
    } else {
        cerr << "Error opening file: " << filePath << endl;
        cout << "Test case for '" << filePath << "': FAIL" << endl;
        return 1;
    }
}

int main() {
    vector<string> filenames = {
        "test_file_1.txt",
        "large_file.txt",
        "file_with_!@#$%^&*()_+[]{};,.txt",
        "file_no_extension",
        "empty_file.txt",
        "non_existent_file.txt",
        "file with spaces.txt",
        "a_very_long_filename_that_exceeds_normal_length_limits_for_filenames.txt",
        "image_file.png",
        "file_with_newlines.txt",
        "file_not_found.txt"
    };

    // ضع هنا مسار مجلد الملفات لديك، مثلاً:
    string base_path = "/home/kali/CLionProjects/llm-generated-code-cpp/tests/gemini/Task121/";

    for (auto& name : filenames) {
        string full_path = base_path + name;
        upload_file_by_path(full_path);
        cout << "--------------------------" << endl;
    }

    return 0;
}
