#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int strcmp(const char *str1, const char *str2);
// #include <stdio.h>
// #include <string.h>

// int main() {
//     char str1[] = "Hello";
//     char str2[] = "World";

//     // Comparing str1 and str2
//     int result = strcmp(str1, str2);

//     if (result < 0) {
//         printf("str1 is less than str2\n");
//     } else if (result > 0) {
//         printf("str1 is greater than str2\n");
//     } else {
//         printf("str1 is equal to str2\n");
//     }

//     return 0;
// }

#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 15
#define FILENAME "contacts.txt"

void clearChoice();

int main() {
    char choice;
    do {
        printf("\nContact Management System\n1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display All Contacts\n5. Exit\nEnter your choice: ");
        scanf(" %c", &choice);
        clearChoice();

        switch (choice) {
            case '1':{
                char name[MAX_NAME_LEN], phone[MAX_PHONE_LEN];
                printf("Enter Name: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0'; 
                printf("Enter Phone Number: ");
                fgets(phone, MAX_PHONE_LEN, stdin);
                phone[strcspn(phone, "\n")] = '\0';
                FILE *file = fopen(FILENAME, "a");
                if (file != NULL) {
                    fprintf(file, "%s,%s\n", name, phone);
                    fclose(file);
                    printf("Contact added successfully.\n");
                } else {
                    printf("Error: Could not open file.\n");
                }
                break;
            }
            case '2':{
                char search[MAX_NAME_LEN];
                printf("Enter name to search: ");
                fgets(search, MAX_NAME_LEN, stdin);
                search[strcspn(search, "\n")] = '\0'; 

                FILE *file = fopen(FILENAME, "r");
                if (file != NULL) {
                    char line[MAX_NAME_LEN + MAX_PHONE_LEN + 2];
                    int found = 0;
                    while (fgets(line, sizeof(line), file) != NULL) {
                        if (strstr(line, search) != NULL) {
                            printf("Contact found: %s", line);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("No contact found.\n");
                    }
                    fclose(file);
                } else {
                    printf("Error: Could not open file.\n");
                }
                break;
            }
            case '3':{
                char deleteContact[MAX_NAME_LEN];
                printf("Enter name to delete: ");
                fgets(deleteContact, MAX_NAME_LEN, stdin);
                deleteContact[strcspn(deleteContact, "\n")] = '\0'; 

                FILE *file = fopen(FILENAME, "r");
                FILE *tempFile = fopen("temp.txt", "w");
                if (file != NULL && tempFile != NULL) {
                    char line[MAX_NAME_LEN + MAX_PHONE_LEN + 2];
                    int deleted = 0;
                    while (fgets(line, sizeof(line), file) != NULL) {
                        if (strstr(line, deleteContact) == NULL) {
                            fputs(line, tempFile);
                        } else {
                            deleted = 1;
                        }
                    }
                    fclose(file);
                    fclose(tempFile);

                    if (deleted) {
                        remove(FILENAME);
                        rename("temp.txt", FILENAME);
                        printf("Contact deleted successfully..\n");
                    } else {
                        printf("Contact not found.\n");
                    }
                } else {
                    printf("Error: Could not open file.\n");
                }
                break;
            }
            case '4':{
                    FILE *file = fopen(FILENAME, "r");
                    if (file != NULL) {
                        char line[MAX_NAME_LEN + MAX_PHONE_LEN + 2];
                        printf("Contact List:\n");
                        printf("===========================\n");
                        while (fgets(line, sizeof(line), file) != NULL) {
                            char name[MAX_NAME_LEN], phone[MAX_PHONE_LEN];
                            sscanf(line, "%99[^,],%14[^\n]", name, phone);
                            printf("Name: %s\n", name);
                            printf("Phone: %s", phone);
                        }
                        printf("\n===========================\n");
                        fclose(file);
                    } else {
                        printf("Error: Could not open file.\n");
                }
                break;
                    
            }
            case '5':
                exit(0);
            default:
                printf("Error: Invalid choice!\n");
        }
    } while (choice != '5');

    return 0;
}

void clearChoice() {
    while (getchar() != '\n'); // Clear the input buffer
}
