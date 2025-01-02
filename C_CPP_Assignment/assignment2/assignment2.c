#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    int choice = 0;
    char inputFile[100];
    char outputFile[100];
    int key = 0;

    printf("Simple File Encryption/Decryption Program\n");
    printf("1. Encrypt a file\n");
    printf("2. Decrypt a file\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the input file name: ");
        scanf("%s", inputFile);
        fptr = fopen(inputFile, "r");
        if (fptr == NULL) {
            printf("File does not exist.\n");
            exit(0);
        } else {
            printf("Enter the output file name: ");
            scanf("%s", outputFile);
            printf("Enter the key (integer): ");
            
            // Check if the key is a valid integer
            if (scanf("%d", &key) != 1) {
                printf("Error: Key must be an integer.\n");
                exit(0);
            }
            
            printf("Valid key: %d\n", key);
            char storage[1000];
            int i = 0;
            int a;
            while ((a = fgetc(fptr)) != EOF) {
                storage[i++] = a + key;  // Encrypt by shifting
            }
            storage[i] = '\0';  // End
            fclose(fptr);
            fptr = fopen(outputFile, "w");
            if (fptr == NULL) {
                printf("Error in handling output file.\n");
                exit(0);
            } else {
                fputs(storage, fptr);  // Write to output file from storage
                printf("Encryption completed. Output saved to '%s'.\n", outputFile);
                fclose(fptr);
                exit(0);
            }
        }
    } else if (choice == 2) {
        printf("Enter the input file name: ");
        scanf("%s", inputFile);
        fptr = fopen(inputFile, "r");
        if (fptr == NULL) {
            printf("File does not exist.\n");
            exit(0);
        } else {
            printf("Enter the output file name: ");
            scanf("%s", outputFile);
            printf("Enter the key (integer): ");
            
            // Check if the key is a valid integer
            if (scanf("%d", &key) != 1) {
                printf("Error: Key must be an integer.\n");
                exit(0);
            }
            
            printf("Valid key: %d\n", key);
            char storage[1000];
            int i = 0;
            int a;
            while ((a = fgetc(fptr)) != EOF) {
                storage[i++] = a - key;  // Encrypt by shifting
            }
            storage[i] = '\0';  // End
            fclose(fptr);
            fptr = fopen(outputFile, "w");
            if (fptr == NULL) {
                printf("Error in handling output file.\n");
                exit(0);
            } else {
                fputs(storage, fptr);  // Write to output file from storage
                printf("Encryption completed. Output saved to '%s'.\n", outputFile);
                fclose(fptr);
                exit(0);
            }
        }
    } else {
        printf("Invalid choice. Please choose 1 or 2.\n");
    }

    return 0;
}
