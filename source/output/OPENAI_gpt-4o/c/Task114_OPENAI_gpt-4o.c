// C
#include <stdio.h>
#include <string.h>

void c_string_operations() {
    char str1[] = "Hello";
    char str2[] = "World";
    char copied_str[6];
    char concatenated_str[12];
    strcpy(copied_str, str1);
    snprintf(concatenated_str, sizeof(concatenated_str), "%s %s", str1, str2);
    printf("C - Copied: %s
", copied_str);
    printf("C - Concatenated: %s
", concatenated_str);
    // For manipulated string: reverse str1 and to uppercase str2
    for (int i = 0, j = strlen(str1) - 1; i < j; i++, j--) {
        char temp = str1[i];
        str1[i] = str1[j];
        str1[j] = temp;
    }
    for (int i = 0; str2[i] != ' '; i++) {
        if (str2[i] >= 'a' && str2[i] <= 'z') {
            str2[i] = str2[i] - 32;
        }
    }
    printf("C - Manipulated: %s %s
", str1, str2);
}

int main() {
    c_string_operations();
    return 0;
}