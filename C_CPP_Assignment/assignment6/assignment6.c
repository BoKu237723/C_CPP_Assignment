#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "dictionary.txt"
#define MAX_WORDNAME 10
#define MAX_DIFINITION 1000
#define LINE_SIZE (MAX_WORDNAME + MAX_DIFINITION)


void clear() {
    while (getchar() != '\n');
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

void addWord(){
    char word[MAX_WORDNAME], definition[MAX_DIFINITION];

    printf("Enter word: ");
    fgets(word, MAX_WORDNAME, stdin);
    word[strcspn(word, "\n")] = '\0';

    printf("Enter definition: ");
    fgets(definition, MAX_DIFINITION, stdin);
    definition[strcspn(definition, "\n")] = '\0';

    FILE *fptr = fopen(FILENAME, "a");
    if (fptr != NULL) {
        fprintf(fptr, "%s|%s\n", word, definition);
        fclose(fptr);
        printf("Word added successfully!\n\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

void displayWords(){
    printf("\nWord               Definition\n");
    printf("---------------------------------\n");
    FILE *fptr = fopen(FILENAME, "r");
    char line[MAX_WORDNAME + MAX_DIFINITION];
    if (fptr != NULL) {
        while (fgets(line, sizeof(line), fptr) != NULL) {
            char word[MAX_WORDNAME], definition[MAX_DIFINITION];
            sscanf(line, "%10[^|]|%999[^\n]", word, definition);
            printf(word);
            for(int i = strlen(word); i< 18; i++){
                printf(" ");
            }
            printf(definition);
            printf("\n");
        }
        printf("\n");
        fclose(fptr);
    }else{
        printf("Error\n\n");
    }
}

void searchWord() {
    char search[MAX_WORDNAME];
    printf("Enter the word to search: ");
    fgets(search, MAX_WORDNAME, stdin);
    search[strcspn(search, "\n")] = '\0';
    toLowerCase(search);

    FILE *fptr = fopen(FILENAME, "r");
    if (fptr != NULL) {
        char line[MAX_WORDNAME + MAX_DIFINITION];
        int found = 0;
        while (fgets(line, sizeof(line), fptr) != NULL) {
            char word[MAX_WORDNAME], definition[MAX_DIFINITION];
            sscanf(line, "%10[^|]|%999[^\n]", word, definition);
            char tempWord[MAX_WORDNAME];
            strncpy(tempWord, word, MAX_WORDNAME);
            toLowerCase(tempWord);

            if (strcmp(tempWord, search) == 0) {
                printf("Definition: %s\n\n", definition);
                found = 1;
                break;
            }
        }
        fclose(fptr);
        if (!found) {
            printf("Word not found.\n\n");
        }
    } else {
        printf("Error opening file.\n\n");
    }
}

void deleteWord() {

    char target[MAX_WORDNAME];
    printf("Enter the word to delete: ");
    fgets(target, MAX_WORDNAME, stdin);
    target[strcspn(target, "\n")] = '\0';

    toLowerCase(target);

    FILE *fptr = fopen(FILENAME, "r");
    if (fptr == NULL) {
        printf("Error: Dictionary file not found.\n");
        return;
    }

    char tempStorage[100][MAX_WORDNAME + MAX_DIFINITION];
    int count = 0, found = 0;

    while (fgets(tempStorage[count], sizeof(tempStorage[0]), fptr) != NULL) {
        char word[MAX_WORDNAME], definition[MAX_DIFINITION];
        sscanf(tempStorage[count], "%10[^|]|%999[^\n]", word, definition);
        char tempWord[MAX_WORDNAME];
        strncpy(tempWord, word, MAX_WORDNAME);
        toLowerCase(tempWord);

        if (strcmp(tempWord, target) != 0) {
            count++;
        } else {
            found = 1;
        }
    }
    fclose(fptr);

    if (found) {
        fptr = fopen(FILENAME, "w");
        if (fptr == NULL) {
            printf("Error\n\n");
            return;
        }
        for (int i = 0; i < count; i++) {
            fprintf(fptr, "%s", tempStorage[i]);
        }
        fclose(fptr);
        printf("Word deleted successfully.\n\n");
    } else {
        printf("Word not found.\n");
    }
}

void updateDefinition() {
    char target[MAX_WORDNAME], newDefinition[MAX_DIFINITION];
    printf("Enter the word to update: ");
    fgets(target, MAX_WORDNAME, stdin);
    target[strcspn(target, "\n")] = '\0';
    toLowerCase(target);

    printf("Enter the new definition: ");
    fgets(newDefinition, MAX_DIFINITION, stdin);
    newDefinition[strcspn(newDefinition, "\n")] = '\0';

    //target | newDefinition

    FILE *fptr = fopen(FILENAME, "r");
    if (fptr != NULL) {
        char tempStoreage[100][MAX_WORDNAME + MAX_DIFINITION];
        int count = 0, found = 0;

        // while (fgets(tempStoreage[count], sizeof(tempStoreage[0]), fptr) != NULL) {
        //     char word[MAX_WORDNAME], definition[MAX_DIFINITION];
        //     sscanf(tempStoreage[0], "%10[^|]|%999[^\n]", word, definition);
        //     char tempWord[MAX_WORDNAME];
        //     strncpy(tempWord, word, MAX_WORDNAME);
        //     toLowerCase(tempWord);

        //     if (strcmp(tempWord, target) == 0) {
        //         //compares the lowercase version of the word with the target
        //         snprintf(tempStoreage[count], sizeof(tempStoreage[count]), "%s|%s\n", word, newDefinition); 
        //         found = 1;
        //     }
        //     count++;
        // }

        while (fgets(tempStoreage[count], LINE_SIZE, fptr) != NULL) {
            char tempWord[MAX_WORDNAME];
            sscanf(tempStoreage[count], "%10[^|]|%*s", tempWord); //only the word
            toLowerCase(tempWord);

            if (strcmp(tempWord, target) == 0) { //comparing
                snprintf(tempStoreage[count], LINE_SIZE, "%s|%s\n", tempWord, newDefinition);
                found = 1;
            }
            count++;
        }

        fclose(fptr);

        if (found) {
            fptr = fopen(FILENAME, "w");
            for (int i = 0; i < count; i++) {
                fprintf(fptr, "%s", tempStoreage[i]);
            }
            fclose(fptr);
            printf("Definition updated successfully.\n\n");
        } else {
            printf("Word not found.\n\n");
        }
    } else {
        printf("Error\n\n");
    }
}

int main() {
    char choice;
    do {
        FILE *fptr = fopen(FILENAME, "r");
        if (fptr == NULL) {
            printf("No exicting dictionary file found. Starting fresh.\n\n");
            fptr = fopen(FILENAME, "w");
        }
        printf("Dictionary Application");
        printf("\n1. Add Word\n2. Display Words\n3. Search Word\n4. Delete Word\n5. Update Definition\n6. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        clear();

        switch (choice) {
            case '1':
                addWord();
                break;
            case '2':
                displayWords();
                break;
            case '3':
                searchWord();
                break;
            case '4':
                deleteWord();
                break;
            case '5':
                updateDefinition();
                break;
            case '6':
                exit(0);
            default:
                printf("Invalid choice. Please choose a valid option.\n");
        }
    } while (choice != '6');
    return 0;
}
