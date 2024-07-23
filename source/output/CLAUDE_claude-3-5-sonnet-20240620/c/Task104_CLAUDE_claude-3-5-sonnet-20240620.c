
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 100
#define INPUT_SIZE 1000

int main() {
    char buffer[BUFFER_SIZE + 1] = {0};
    char input[INPUT_SIZE];
    
    while (true) {
        printf("Enter text (or 'q' to quit): ");
        if (fgets(input, INPUT_SIZE, stdin) == NULL) {
            break;
        }
        
        // Remove newline character
        input[strcspn(input, "\\n")] = 0;
        
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) {
            break;
        }
        
        if (strlen(buffer) + strlen(input) <= BUFFER_SIZE) {
            strcat(buffer, input);
            printf("Buffer content: %s\\n", buffer);
        } else {
            printf("Error: Buffer overflow. Cannot add more than %d characters.\\n", BUFFER_SIZE);
        }
    }
    
    printf("Final buffer content: %s\\n", buffer);
    return 0;
}
