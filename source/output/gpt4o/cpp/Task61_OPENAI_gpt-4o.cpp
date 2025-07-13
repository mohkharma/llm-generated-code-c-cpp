#include <iostream>
#include <string>
#include <tinyxml2.h>

void printRootElementNameFromXML(const std::string& xmlContent) {
    tinyxml2::XMLDocument doc;
    if (doc.Parse(xmlContent.c_str()) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = doc.RootElement();
        if (root) {
            std::cout << root->Name() << std::endl;
        }
    } else {
        std::cerr << "Failed to parse XML" << std::endl;
    }
}
