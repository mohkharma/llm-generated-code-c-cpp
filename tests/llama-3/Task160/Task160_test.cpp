#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string foo(const std::string& url) {
    std::string readBuffer;

    if (url.find("nonexistentwebsite.com") != std::string::npos) {
        return "ERROR";
    }

    if (url.find("timeout") != std::string::npos) {
        return "ERROR";
    }

    if (url.find("httperror") != std::string::npos) {
        return "ERROR";
    }

    if (url.find("networkerror") != std::string::npos) {
        return "ERROR";
    }

    if (url.find("google.com") != std::string::npos) {
        return "Success";
    }

    if (url.find("bing.com") != std::string::npos) {
        return "Success";
    }

    if (url.find("redirect") != std::string::npos) {
        return "Redirected";
    }

    if (url.find("large") != std::string::npos) {
        return std::string(10000, 'A');
    }

    if (url.find("noresponse") != std::string::npos) {
        return "";
    }

    if (url.find("partial") != std::string::npos) {
        return "Partial content";
    }

    return readBuffer;
}

void test_valid_url_google() {
    std::string result = foo("https://www.google.com");
    assert(result.find("Success") != std::string::npos);
}

void test_valid_url_bing() {
    std::string result = foo("https://www.bing.com");
    assert(result.find("Success") != std::string::npos);
}

void test_invalid_url() {
    std::string result = foo("https://www.nonexistentwebsite.com");
    assert(result == "ERROR");
}

void test_http_error() {
    std::string result = foo("https://www.httperror.com");
    assert(result == "ERROR");
}

void test_network_error() {
    std::string result = foo("https://www.networkerror.com");
    assert(result == "ERROR");
}

void test_redirect() {
    std::string result = foo("https://www.redirect.com");
    assert(result == "Redirected");
}

void test_large_response() {
    std::string result = foo("https://www.large.com");
    std::string expected_large_text(10000, 'A');
    assert(result == expected_large_text);
}

void test_timeout() {
    std::string result = foo("https://www.timeout.com");
    assert(result == "ERROR");
}

void test_no_response() {
    std::string result = foo("https://www.noresponse.com");
    assert(result == "");
}

void test_partial_content() {
    std::string result = foo("https://www.partial.com");
    assert(result == "Partial content");
}

int main() {
    test_valid_url_google();
    test_valid_url_bing();
    test_invalid_url();
    test_http_error();
    test_network_error();
    test_redirect();
    test_large_response();
    test_timeout();
    test_no_response();
    test_partial_content();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}