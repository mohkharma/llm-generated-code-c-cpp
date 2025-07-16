#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <xpath_value> <xml_file_name>" << std::endl;
        return 1;
    }

    std::string xpathValue = argv[1];
    std::string xmlFileName = argv[2];

    xmlDoc *doc = xmlReadFile(xmlFileName.c_str(), NULL, 0);
    if (doc == NULL) {
        std::cerr << "Failed to parse XML file" << std::endl;
        return 1;
    }

    xmlXPathContext *context = xmlXPathNewContext(doc);
    if (context == NULL) {
        std::cerr << "Failed to create XPath context" << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }

std::string xpathExpr = xpathValue;
    xmlXPathObject *result = xmlXPathEvalExpression((xmlChar *)xpathExpr.c_str(), context);
    if (result == NULL) {
        std::cerr << "Failed to evaluate XPath expression" << std::endl;
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return 1;
    }

    xmlNodeSet *nodeset = result->nodesetval;

    if (xmlXPathNodeSetIsEmpty(nodeset)) {
        std::cout << "No result" << std::endl;
    } else {
        for (int i = 0; i < nodeset->nodeNr; i++) {
            xmlNode *node = nodeset->nodeTab[i];
            xmlChar* content = xmlNodeGetContent(node);
            if (content) {
                std::cout << content << std::endl;
                xmlFree(content);
            }
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    return 0;
}

/*
 * How to Run the Code? =>:
┌──(kali㉿kali)-[~/CLionProjects/llm-generated-code-cpp/cmake-build-debug]
└─$ ./Task61_Test "/library/book[@id='1']/author" /home/kali/CLionProjects/llm-generated-code-cpp/tests/llama-3/Task97/xmlExample.xml

Joshua Bloch

 */