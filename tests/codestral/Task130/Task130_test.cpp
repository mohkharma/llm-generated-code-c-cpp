#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

int run_tests() {
    int passed = 0;
    int total = 1;

    cout << "[TEST 1] Running external solution binary (./Task130)..." << endl;

    int result = system("./Task130"); // يجب أن يكون الملف التنفيذي مكوَّن مسبقًا

    if (result == 0) {
        cout << "[PASS] Server ran without crashing (exit code 0)" << endl;
        passed++;
    } else {
        cout << "[FAIL] Server crashed or exited abnormally (exit code " << result << ")" << endl;
    }

    cout << "------------------------" << endl;
    cout << "Passed " << passed << " out of " << total << " tests." << endl;

    return 0;
}

int main() {
    return run_tests();
}
