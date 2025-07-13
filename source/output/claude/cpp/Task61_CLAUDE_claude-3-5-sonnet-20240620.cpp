
#include <iostream>
#include <string>
#include <pugixml.hpp>

std::string get_root_element(const std::string& xml_string) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml_string.c_str());
    
    if (result) {
        pugi::xml_node root = doc.document_element();
        return root.name();
    } else {
        return "Error parsing XML";
    }
}
