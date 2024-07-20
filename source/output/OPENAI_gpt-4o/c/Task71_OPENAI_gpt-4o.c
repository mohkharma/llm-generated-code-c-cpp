#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char *end;
        int num = strtol(argv[1], &end, 10);
        if (*end == ' ') {
            printf("C: Converted integer is %d
", num);
        } else {
            printf("C: Invalid number
");
        }
    } else {
        printf("C: Please provide an input
");
    }
    return 0;
}