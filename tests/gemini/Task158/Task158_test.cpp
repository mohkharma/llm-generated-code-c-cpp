#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdio>  // popen, pclose

using namespace std;

string runProgramWithInput(const string& inputCommand) {
    // محاكاة تشغيل البرنامج مع إدخال الأمر inputCommand
    // نريد أن نحاكي:
    // - طباعة رسالة الإدخال
    // - تنفيذ الأمر inputCommand عبر system()
    // ثم نلتقط كل الإخراج

    // ندمج طباعة الرسالة مع إخراج تنفيذ الأمر

    // نفترض أن البرنامج الأصلي يطبع "Enter OS command: "
    string prompt = "Enter OS command: ";

    // ننفذ الأمر inputCommand عبر popen لالتقاط ناتجه
    FILE* pipe = popen(inputCommand.c_str(), "r");
    if (!pipe) return "ERROR\n";

    char buffer[128];
    string commandOutput;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        commandOutput += buffer;
    }
    pclose(pipe);

    // نرجع ناتج الدمج
    return prompt + commandOutput;
}

void test() {
    // نجرب أمر بسيط معروف
    string testCommand = "echo HelloTest123";
    string expectedOutput = "Enter OS command: HelloTest123\n";

    string actualOutput = runProgramWithInput(testCommand);

    assert(actualOutput == expectedOutput && "Output does not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
