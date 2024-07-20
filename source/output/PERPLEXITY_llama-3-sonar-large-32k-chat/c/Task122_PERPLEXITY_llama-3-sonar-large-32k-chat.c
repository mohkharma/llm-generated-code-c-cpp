#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[100];
int userCount = 0;

void signup() {
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    userCount++;
    printf("Signup successful!
");
}

int main() {
    while (true) {
        printf("1. Signup
");
        printf("2. Exit
");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            signup();
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid choice. Please try again.
");
        }
    }
    return 0;
}