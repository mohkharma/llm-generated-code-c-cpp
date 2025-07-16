#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_test(const char* hostname, const char* username, const char* password, const char* filename, const char* expected_success_substring, const char* expected_failure_substring) {
    char cmd[512];
    const char* executable = "./ftp_downloader"; // اسم البرنامج التنفيذي عندك
    const char* output_file = "test_output.txt";

    // تنفذ البرنامج مع تحويل الإخراج إلى ملف نصي
    snprintf(cmd, sizeof(cmd), "%s %s %s %s %s > %s 2>&1", executable, hostname, username, password, filename, output_file);

    int ret = system(cmd);
    if (ret != 0) {
        printf("FAIL (program exited with code %d)\n", ret);
        return 0;
    }

    FILE* f = fopen(output_file, "r");
    if (!f) {
        printf("FAIL (cannot open output file)\n");
        return 0;
    }

    char buffer[1024];
    int success_found = 0;
    int failure_found = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, expected_success_substring)) success_found = 1;
        if (expected_failure_substring && strstr(buffer, expected_failure_substring)) failure_found = 1;
    }
    fclose(f);
    remove(output_file);

    if (success_found && !failure_found) {
        printf("PASS\n");
        return 1;
    } else if (failure_found) {
        printf("FAIL (detected failure message)\n");
        return 0;
    } else {
        printf("FAIL (expected success message not found)\n");
        return 0;
    }
}

int main() {
    int passed = 0, failed = 0;

    // عيّن حالات الاختبار بنفس الترتيب والبيانات من بايثون
    printf("Test Case 1: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "testfile.txt", "", "cURL error"))
        passed++;
    else
        failed++;

    printf("Test Case 2: ");
    if (run_test("invalid.host", "user2", "pass2", "testfile.txt", "cURL error", "cURL error"))
        passed++;
    else
        failed++;

    printf("Test Case 3: ");
    if (run_test("ftp.testserver.com", "invalid", "invalid", "testfile.txt", "cURL error", "cURL error"))
        passed++;
    else
        failed++;

    printf("Test Case 4: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "missing.txt", "cURL error", "cURL error"))
        passed++;
    else
        failed++;

    printf("\nSummary: Passed: %d, Failed: %d\n", passed, failed);
    return 0;
}
