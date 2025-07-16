#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_test(const char* hostname, const char* username, const char* password, const char* filename, const char* expected_output_substring) {
    char cmd[512];
    char output_file[] = "test_output.txt";

    // بناء أمر التنفيذ مع إعادة التوجيه لإخراج في ملف مؤقت
    snprintf(cmd, sizeof(cmd), "./ftp_downloader %s %s %s %s > %s 2>&1", hostname, username, password, filename, output_file);

    int ret = system(cmd);
    if (ret != 0) {
        printf("FAIL (program exited with code %d)\n", ret);
        return 0;
    }

    // فتح الملف المؤقت وقراءة المحتوى
    FILE* f = fopen(output_file, "r");
    if (!f) {
        printf("FAIL (cannot open output file)\n");
        return 0;
    }

    char buffer[1024];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, expected_output_substring) != NULL) {
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
    int pass_count = 0, fail_count = 0;

    printf("Test Case 1: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "testfile.txt", "downloaded successfully"))
        pass_count++;
    else
        fail_count++;

    printf("Test Case 2: ");
    if (run_test("invalid.host", "user2", "pass2", "testfile.txt", "An error occurred"))
        pass_count++;
    else
        fail_count++;

    printf("Test Case 3: ");
    if (run_test("ftp.testserver.com", "invalid", "invalid", "testfile.txt", "An error occurred"))
        pass_count++;
    else
        fail_count++;

    printf("Test Case 4: ");
    if (run_test("ftp.testserver.com", "user1", "pass1", "missing.txt", "An error occurred"))
        pass_count++;
    else
        fail_count++;

    printf("\nSummary: Passed: %d, Failed: %d\n", pass_count, fail_count);

    return 0;
}
