#include <cassert>
#include "../../../source/output/gpt4o/cpp/Task110_OPENAI_gpt-4o.cpp"

void testFoo() {
    // Test cases
    assert(foo("http://example.com") == 1);  // Valid HTTP URL
    assert(foo("https://example.com") == 1); // Valid HTTPS URL
    assert(foo("ftp://example.com") == 1);   // Valid FTP URL
    assert(foo("http://localhost") == 1);    // Valid localhost URL
    assert(foo("http://127.0.0.1") == 1);    // Valid IPv4 URL
    assert(foo("http://[::1]") == 1);        // Valid IPv6 URL
    assert(foo("http://example.com:8080") == 1); // Valid URL with port
    assert(foo("example.com") == 0);         // Invalid URL missing scheme

    assert(foo("http://example") == 0);      // Invalid URL with invalid TLD
    assert(foo("http://-example.com") == 0); // Invalid URL with invalid domain
    // Additional test case to ensure quit breaks loop
    assert(foo("quit") == 0); // Should exit loop and return 0
}

int main() {
    testFoo();
    return 0;
}