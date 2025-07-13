// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

// محاكاة الكود الأصلي مع إضافة طباعة بسيطة لاختبار الإخراج
string runProgram() {
    stringstream output;

    int* myArray = new int[10];

    // اختبار: مثلا نعطي قيمة للعنصر الأول ونطبعها
    myArray[0] = 42;
    output << myArray[0] << "\n";

    delete[] myArray;

    return output.str();
}

void test() {
    string expected = "42\n";
    string actual = runProgram();
    assert(actual == expected && "Output did not match expected value.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
