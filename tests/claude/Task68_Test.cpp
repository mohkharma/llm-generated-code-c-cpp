#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// لا تغير في الدالة extractDcAndUsername كما طلبت، سأعيد كتابتها هنا لأغراض الاختبار فقط
void extractDcAndUsername(const char* inputString, char* username, char* dc) {
    const char* atPos = strchr(inputString, '@');
    if (!atPos) {
        username[0] = '\0';
        dc[0] = '\0';
        return;
    }
    size_t userLen = atPos - inputString;
    strncpy(username, inputString, userLen);
    username[userLen] = '\0';

    const char* domain = atPos + 1;
    dc[0] = '\0';

    char domainCopy[256];
    strncpy(domainCopy, domain, sizeof(domainCopy)-1);
    domainCopy[sizeof(domainCopy)-1] = '\0';

    char* token = strtok(domainCopy, ".");
    while (token != NULL) {
        strcat(dc, "dc=");
        strcat(dc, token);
        token = strtok(NULL, ".");
        if (token != NULL) {
            strcat(dc, ",");
        }
    }
}

// دالة مقارنة
bool stringsEqual(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

// دالة اختبار
void test_extractDcAndUsername(const char* input, const char* expectedUser, const char* expectedDc) {
    char username[128];
    char dc[256];
    extractDcAndUsername(input, username, dc);
    printf("Test input: %s\n", input);
    if (stringsEqual(username, expectedUser) && stringsEqual(dc, expectedDc)) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("  Expected username: %s, Got: %s\n", expectedUser, username);
        printf("  Expected dc: %s, Got: %s\n", expectedDc, dc);
    }
}

// Main function to run tests
int main() {
    // ضع هنا التست كيسز من البايثون، مثال:
    test_extractDcAndUsername("john@domain.com", "john", "dc=domain,dc=com");
    test_extractDcAndUsername("alice@example.org", "alice", "dc=example,dc=org");
    test_extractDcAndUsername("bob@sub.domain.co.uk", "bob", "dc=sub,dc=domain,dc=co,dc=uk");
    test_extractDcAndUsername("invalidstring", "", "");
    test_extractDcAndUsername("noatsign.com", "", "");
    return 0;
}
