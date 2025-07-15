#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <xpath_expression> <xml_file>" << std::endl;
        return 1;
    }

    const char* xpathExpr = argv[1];
    const char* xmlFile = argv[2];

    // Initialize libxml
    xmlInitParser();

    // Parse XML file
    xmlDocPtr doc = xmlReadFile(xmlFile, NULL, 0);
    if (doc == NULL) {
        std::cerr << "Failed to parse " << xmlFile << std::endl;
        xmlCleanupParser();
        return 1;
    }

    // Create XPath evaluation context
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        std::cerr << "Error: unable to create new XPath context" << std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    // Evaluate XPath expression
    xmlXPathObjectPtr result = xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>(xpathExpr), context);
    if (result == NULL) {
        std::cerr << "Error: unable to evaluate xpath expression" << std::endl;
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    // Check for empty result
    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        std::cout << "No result" << std::endl;
    } else {
        xmlNodeSetPtr nodeset = result->nodesetval;
        // Iterate over nodes and print their text content
        for (int i = 0; i < nodeset->nodeNr; ++i) {
            xmlNodePtr node = nodeset->nodeTab[i];
            xmlChar* content = xmlNodeGetContent(node);
            if (content) {
                std::cout << content << std::endl;
                xmlFree(content);
            }
        }
    }

    // Cleanup
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}

/*
 Here is how to run the code =>
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test "/library/book[@id='1']/author" "/home/kali/CLionProjects/llm-generated-code-cpp/tests/claude/Task97/xmlExample.xml"

Joshua Bloch

 */