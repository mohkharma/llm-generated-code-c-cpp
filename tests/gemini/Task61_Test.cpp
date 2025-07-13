#include "../../source/output/gemini/cpp/Task61_GEMINI_gemini-1.5-pro-001.cpp"  // عدّل حسب المسار الفعلي

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

int tests_passed = 0;
int tests_failed = 0;

void print_result(const std::string& test_name, const std::string& expected, const std::string& actual) {
    if (expected == actual) {
        std::cout << "[PASS] " << test_name << std::endl;
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "  Expected: " << expected << std::endl;
        std::cout << "  Got     : " << actual << std::endl;
        tests_failed++;
    }
}

void test_basic_xml() {
    std::string xml = "<root><child1>Content</child1><child2 attr=\"value\"/></root>";
    print_result("test_basic_xml", "root", getRootElement(xml));
}

void test_single_element_xml() {
    std::string xml = "<single/>";
    print_result("test_single_element_xml", "single", getRootElement(xml));
}

void test_nested_elements() {
    std::string xml = "<parent><child><subchild/></child></parent>";
    print_result("test_nested_elements", "parent", getRootElement(xml));
}

void test_empty_document() {
    std::string xml = "<empty></empty>";
    print_result("test_empty_document", "empty", getRootElement(xml));
}

void test_self_closing_tag() {
    std::string xml = "<selfclosing attr=\"value\"/>";
    print_result("test_self_closing_tag", "selfclosing", getRootElement(xml));
}

void test_xml_with_attributes() {
    std::string xml = "<root attr=\"value\"><child/></root>";
    print_result("test_xml_with_attributes", "root", getRootElement(xml));
}

void test_multiple_root_elements() {
    std::string xml = "<root1/><root2/>";
    try {
        std::string result = getRootElement(xml);
        std::cout << "[FAIL] test_multiple_root_elements" << std::endl;
        std::cout << "  Expected exception but got: " << result << std::endl;
        tests_failed++;
    } catch (...) {
        std::cout << "[PASS] test_multiple_root_elements" << std::endl;
        tests_passed++;
    }
}

void test_large_xml() {
    std::ostringstream oss;
    oss << "<root>";
    for (int i = 0; i < 1000; ++i)
        oss << "<child>";
    for (int i = 0; i < 1000; ++i)
        oss << "</child>";
    oss << "</root>";
    print_result("test_large_xml", "root", getRootElement(oss.str()));
}

void test_malformed_xml() {
    std::string xml = "<root><child></root>";
    try {
        std::string result = getRootElement(xml);
        std::cout << "[FAIL] test_malformed_xml" << std::endl;
        std::cout << "  Expected exception but got: " << result << std::endl;
        tests_failed++;
    } catch (...) {
        std::cout << "[PASS] test_malformed_xml" << std::endl;
        tests_passed++;
    }
}

void test_xml_with_namespaces() {
    std::string xml = "<ns:root xmlns:ns=\"http://example.com\"><ns:child/></ns:root>";
    print_result("test_xml_with_namespaces", "{http://example.com}root", getRootElement(xml));
}

int main() {
    test_basic_xml();
    test_single_element_xml();
    test_nested_elements();
    test_empty_document();
    test_self_closing_tag();
    test_xml_with_attributes();
    test_multiple_root_elements();
    test_large_xml();
    test_malformed_xml();
    test_xml_with_namespaces();

    std::cout << "\nTests passed: " << tests_passed << std::endl;
    std::cout << "Tests failed: " << tests_failed << std::endl;

    return 0;
}
