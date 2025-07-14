#include <iostream>
#include <string>
#include <curl/curl.h>
#include <gumbo.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string get_title_text(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return "";
    }
    if (node->v.element.tag == GUMBO_TAG_TITLE) {
        if (node->v.element.children.length > 0) {
            GumboNode* title_text = static_cast<GumboNode*>(node->v.element.children.data[0]);
            if (title_text->type == GUMBO_NODE_TEXT) {
                return std::string(title_text->v.text.text);
            }
        }
        return "";
    }
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        std::string result = get_title_text(static_cast<GumboNode*>(children->data[i]));
        if (!result.empty()) return result;
    }
    return "";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <url>" << std::endl;
        return 1;
    }

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(!curl) {
        std::cout << "Error: curl init failed" << std::endl;
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
        std::cout << "Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_cleanup(curl);

    GumboOutput* output = gumbo_parse(readBuffer.c_str());
    std::string title = get_title_text(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    if (title.empty()) {
        std::cout << "Page title: No title found" << std::endl;
    } else {
        std::cout << "Page title: " << title << std::endl;
    }

    return 0;
}


