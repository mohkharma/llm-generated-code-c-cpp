#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include <string>
#include <stdexcept>

using namespace xercesc;

std::string getRootElement(const std::string& xmlContent) {
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& e) {
        throw std::runtime_error("Xerces initialization failed.");
    }

    std::string result;

    try {
        XercesDOMParser parser;
        MemBufInputSource memBuf(
            reinterpret_cast<const XMLByte*>(xmlContent.c_str()),
            xmlContent.length(),
            "xml_buffer",
            false
        );
        parser.parse(memBuf);
        DOMDocument* doc = parser.getDocument();
        DOMElement* root = doc->getDocumentElement();

        if (!root)
            throw std::runtime_error("No root element found");

        char* tagName = XMLString::transcode(root->getTagName());
        result = tagName;
        XMLString::release(&tagName);

    } catch (...) {
        XMLPlatformUtils::Terminate();
        throw;  // rethrow to be caught by the test
    }

    XMLPlatformUtils::Terminate();
    return result;
}
