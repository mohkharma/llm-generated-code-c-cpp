#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // 1MB

int main() {
    char filename[256];
    char file_data[MAX_FILE_SIZE];
    long file_size;

    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file.
");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    if (file_size > MAX_FILE_SIZE) {
        printf("File too large.
");
        fclose(fp);
        return 1;
    }

    fread(file_data, sizeof(char), file_size, fp);
    fclose(fp);

    // At this point, the file data is stored in the 'file_data' array.
    // You can now process or save it as needed.

    printf("File uploaded successfully.
");

    return 0;
}