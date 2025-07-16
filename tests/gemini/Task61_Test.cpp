#include <iostream>
#include <string>
#include <stdexcept>
#include "pugixml.hpp"

using namespace std;

string getRootElement(const string& xmlString) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xmlString.c_str());
    if (!result) {
        throw runtime_error("XML parse error");
    }
    pugi::xml_node root = doc.first_child();
    return root.name();
}

// تابع لمقارنة نتيجه الدالة مع المتوقع
void test_case(const string& xml, const string& expected, bool expect_exception = false) {
    try {
        string root = getRootElement(xml);
        if (expect_exception) {
            cout << "FAIL (expected exception but got result: " << root << ")\n";
        } else if (root == expected) {
            cout << "PASS\n";
        } else {
            cout << "FAIL (expected: " << expected << ", got: " << root << ")\n";
        }
    } catch (const exception& e) {
        if (expect_exception) {
            cout << "PASS\n";
        } else {
            cout << "FAIL (unexpected exception: " << e.what() << ")\n";
        }
    }
}

int main() {
    cout << "Test case 1: ";
    test_case("<root><child1>Content</child1><child2 attr=\"value\"/></root>", "root");

    cout << "Test case 2: ";
    test_case("<single/>", "single");

    cout << "Test case 3: ";
    test_case("<parent><child><subchild/></child></parent>", "parent");

    cout << "Test case 4: ";
    test_case("<empty></empty>", "empty");

    cout << "Test case 5: ";
    test_case("<selfclosing attr=\"value\"/>", "selfclosing");

    cout << "Test case 6: ";
    test_case("<root attr=\"value\"><child/></root>", "root");

    cout << "Test case 7 (multiple root elements): ";
    test_case("<root1/><root2/>", "", true);  // Exception expected

    cout << "Test case 8 (large xml): ";
    {
        string xml = "<root>";
        for (int i = 0; i < 1000; ++i) xml += "<child>";
        for (int i = 0; i < 1000; ++i) xml += "</child>";
        xml += "</root>";
        test_case(xml, "root");
    }

    cout << "Test case 9 (malformed xml): ";
    test_case("<root><child></root>", "", true);  // Exception expected

    cout << "Test case 10 (namespaces): ";
    test_case("<ns:root xmlns:ns=\"http://example.com\"><ns:child/></ns:root>", "ns:root");

    return 0;
}
