// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <cassert>

using namespace std;

string runTest() {
    // محاكاة الإدخال:
    // 3 (حجم البافر)
    // "apple", "banana", "cherry" (البيانات)
    // 0, 2, 5 (خارج النطاق), "abc" (خطأ إدخال), -1 (خروج)
    stringstream input(
        "3\n"
        "apple\n"
        "banana\n"
        "cherry\n"
        "0\n"
        "2\n"
        "5\n"
        "abc\n"
        "-1\n"
    );

    stringstream output;

    // إعادة توجيه cin, cout, cerr إلى stream الخاص بالاختبار
    streambuf* cinbuf = cin.rdbuf();
    streambuf* coutbuf = cout.rdbuf();
    streambuf* cerrbuf = cerr.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());
    cerr.rdbuf(output.rdbuf());

    // بداية منطق البرنامج (بنفس كودك الأصلي)
    int size;

    cout << "Enter the size of the buffer: ";
    cin >> size;

    if (cin.fail() || size <= 0) {
        cerr << "Invalid input. Please enter a positive integer." << endl;

        // استعادة الدفق قبل الإرجاع
        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);
        cerr.rdbuf(cerrbuf);
        return output.str();
    }

    string* buffer = new string[size];

    for (int i = 0; i < size; i++) {
        cout << "Enter data for index " << i << ": ";
        cin >> buffer[i];
    }

    while (true) {
        int index;
        cout << "Enter an index to read data (or -1 to exit): ";
        cin >> index;

        if (cin.fail()) {
            cerr << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (index == -1) {
            break;
        } else if (index >= 0 && index < size) {
            cout << "Data at index " << index << ": " << buffer[index] << endl;
        } else {
            cout << "Index out of range." << endl;
        }
    }

    delete[] buffer;

    // استعادة دفق الإدخال والإخراج
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    cerr.rdbuf(cerrbuf);

    return output.str();
}

void test() {
    string expected =
        "Enter the size of the buffer: "
        "Enter data for index 0: "
        "Enter data for index 1: "
        "Enter data for index 2: "
        "Enter an index to read data (or -1 to exit): Data at index 0: apple\n"
        "Enter an index to read data (or -1 to exit): Data at index 2: cherry\n"
        "Enter an index to read data (or -1 to exit): Index out of range.\n"
        "Enter an index to read data (or -1 to exit): Invalid input. Please enter an integer.\n"
        "Enter an index to read data (or -1 to exit): ";

    string actual = runTest();

    assert(actual == expected && "Output does not match expected.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
