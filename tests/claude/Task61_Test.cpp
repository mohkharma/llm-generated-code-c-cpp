#include <iostream>
#include <sstream>
#include <string>
#include "../../source/output/claude/cpp/Task61_CLAUDE_claude-3-5-sonnet-20240620.cpp"
// غير المسار حسب موقع الحل

bool test_basic_xml() {
    std::string input = "<root><child1>Content</child1><child2 attr=\"value\"/></root>";
    std::string expected = "root";
    std::string actual = get_root_element(input);
    return actual == expected;
}

bool test_single_element_xml() {
    std::string input = "<single/>";
    std::string expected = "single";
    std::string actual = get_root_element(input);
    return actual == expected;
}

bool test_nested_elements() {
    std::string input = "<parent><child><subchild/></child></parent>";
    std::string expected = "parent";
    std::string actual = get_root_element(input);
    return actual == expected;
}

bool test_empty_document() {
    std::string input = "<empty></empty>";
    std::string expected = "empty";
    std::string actual = get_root_element(input);
    return actual == expected;
}

bool test_self_closing_tag() {
    std::string input = "<selfclosing attr=\"value\"/>";
    std::string expected = "selfclosing";
    std::string actual = get_root_element(input);
    return actual == expected;
}

bool test_xml_with_attributes() {
    std::string input = "<root attr=\"value\"><child/></root>";
    std::string expected = "root";
    std::string actual = get_root_element(input);
    return actual == expected;
}

// الاختبار الخاص بالعناصر الجذرية المتعددة ينتظر استثناء.
// لكن C++ لا تتعامل مع الاستثناء مثل Python هنا،
// لذلك سنفحص أن النتيجة إما تشير لخطأ أو شيء آخر يدل على فشل التفسير.
bool test_multiple_root_elements() {
    std::string input = "<root1/><root2/>";
    std::string result = get_root_element(input);
    // يتوقع أن لا تكون "root1" أو "root2" فقط.
    // الحل قد يرجع "Error parsing XML" أو شيء مشابه.
    // بناءً على الحل، نعتبر النتيجة "غير صحيحة" لو أعطى اسم جذر صحيح.
    if (result == "root1" || result == "root2") {
        return false;
    }
    // تقبل رسالة خطأ
    return true;
}

bool test_large_xml() {
    std::string input = "<root>";
    for (int i = 0; i < 1000; i++) input += "<child>";
    for (int i = 0; i < 1000; i++) input += "</child>";
    input += "</root>";
    std::string expected = "root";
    std::string actual = get_root_element(input);
    return actual == expected;
}

// اختبار XML مع وجود خطأ نحوي (Malformed XML)
// يجب أن ينتج خطأ أو قيمة تدل على فشل التفسير
bool test_malformed_xml() {
    std::string input = "<root><child></root>";
    std::string result = get_root_element(input);
    // نتوقع أن تكون النتيجة رسالة خطأ أو غير صحيحة
    return result != "root" && result != "child";
}

// اختبار XML مع مساحات أسماء (Namespaces)
bool test_xml_with_namespaces() {
    std::string input = "<ns:root xmlns:ns=\"http://example.com\"><ns:child/></ns:root>";
    std::string expected = "{http://example.com}root";
    std::string actual = get_root_element(input);
    return actual == expected;
}

int main() {
    int passed = 0, failed = 0;

    #define RUN_TEST(test) \
        if (test()) { \
            std::cout << "[PASS] " #test << std::endl; ++passed; \
        } else { \
            std::cout << "[FAIL] " #test << std::endl; ++failed; \
        }

    RUN_TEST(test_basic_xml);
    RUN_TEST(test_single_element_xml);
    RUN_TEST(test_nested_elements);
    RUN_TEST(test_empty_document);
    RUN_TEST(test_self_closing_tag);
    RUN_TEST(test_xml_with_attributes);
    RUN_TEST(test_multiple_root_elements);
    RUN_TEST(test_large_xml);
    RUN_TEST(test_malformed_xml);
    RUN_TEST(test_xml_with_namespaces);

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of 10 tests." << std::endl;
    if (failed > 0) {
        std::cout << "Failed " << failed << " tests." << std::endl;
        return 1;
    }
    return 0;
}
