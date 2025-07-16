#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_test(const char* hostname, const char* username, const char* password, const char* filename, const char* expected_substring) {
    char cmd[512];
    const char* executable = "./ftp_downloader"; // تأكد من اسم الملف التنفيذي هنا
    char output_file[] = "test_output.txt";

    // بناء أمر التنفيذ مع توجيه الإخراج لملف نصي
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
    int found = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, expected_substring) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(f);
    remove(output_file);

    if (found) {
        printf("PASS\n");
        return 1;
    } else {
        printf("FAIL (expected output not found)\n");
        return 0;
    }
}

int main() {
    int passed = 0, failed = 0;

    printf("Test Case 1: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "testfile.txt", "downloaded successfully"))
        passed++;
    else
        failed++;

    printf("Test Case 2: ");
    if (run_test("invalid.host", "user2", "pass2", "testfile.txt", "curl_easy_perform() failed"))
        passed++;
    else
        failed++;

    printf("Test Case 3: ");
    if (run_test("ftp.testserver.com", "invalid", "invalid", "testfile.txt", "curl_easy_perform() failed"))
        passed++;
    else
        failed++;

    printf("Test Case 4: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "missing.txt", "curl_easy_perform() failed"))
        passed++;
    else
        failed++;

    printf("\nSummary: Passed: %d, Failed: %d\n", passed, failed);

    return 0;
}
