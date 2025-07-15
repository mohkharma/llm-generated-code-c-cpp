#include <iostream>
#include <string>
#include <pugixml.hpp>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <xpath_expression> <xml_file> <id_value>" << std::endl;
        return 1;
    }

    const char* xpath_expression = argv[1];
    const char* xml_file_path = argv[2];
    const char* id_value = argv[3];

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_file_path);

    if (!result) {
        std::cerr << "Error parsing XML: " << result.description() << std::endl;
        return 1;
    }

    // يبني XPath كامل مثل: /library/book[@id='1']/author
    std::string full_xpath = std::string(xpath_expression) + "[@id='" + id_value + "']";

    pugi::xpath_query query(full_xpath.c_str());
    pugi::xpath_node_set nodes = query.evaluate_node_set(doc);

    if (nodes.empty()) {
        std::cout << "No result" << std::endl;
        return 0;
    }

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        pugi::xml_node node = it->node();
        std::cout << node.child_value() << std::endl;  // يطبع محتوى النص داخل العنصر
    }

    return 0;
}

/*
 * how to run the code?  =>
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test "/library/book[@id='1']/author" "/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task97/xmlExample.xml"

Joshua Bloch

 */
