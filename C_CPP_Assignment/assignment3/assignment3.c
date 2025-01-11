#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BOOKS 1000
#define MAX_STRING 100

//int result1 = strcmp(string1, string2);

struct Book {
    char BookID[MAX_STRING];
    char Title[MAX_STRING];
    char Author[MAX_STRING];
};

int isValidChoice(const char *choice) {
    return strlen(choice) == 1 && isdigit(choice[0]) && choice[0] >= '1' && choice[0] <= '5';
}

int main() {
    struct Book books[MAX_BOOKS];
    int booksInArray = 0;
    char choice[MAX_STRING];

    do {
        printf("\nBook Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Display All Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (!isValidChoice(choice)) {
            printf("Invalid choice. \n");
            continue;
        }

        switch (choice[0]) {
            case '1': {
                if (booksInArray >= MAX_BOOKS) {
                    printf("Book array is full!\n");
                    break;
                }
                struct Book newBook;
                printf("Enter Book ID: ");
                scanf("%s", newBook.BookID);
                printf("Enter Book Title: ");
                scanf("%s", newBook.Title);
                printf("Enter Book Author: ");
                scanf("%s", newBook.Author);
                books[booksInArray++] = newBook;
                printf("Book added successfully.\n");
                break;
            }
            case '2': {
                char bookID[MAX_STRING];
                printf("Enter Book ID to delete: ");
                scanf("%s", bookID);

                int found = 0;
                for (int i = 0; i < booksInArray; i++) {
                    if (strcmp(books[i].BookID, bookID) == 0) {
                        found = 1;
                        for (int j = i; j < booksInArray - 1; j++) {
                            books[j] = books[j + 1];
                        }
                        booksInArray--;
                        printf("Book with ID '%s' deleted successfully.\n", bookID);
                        break;
                    }
                }
                if (!found) {
                    printf("Error: Book with ID '%s' not found.\n", bookID);
                }
                break;
            }
            case '3': {
                char searchInput[MAX_STRING];
                printf("Enter Book Title or ID to search: ");
                scanf(" %[^\n]", searchInput);

                int found = 0;
                for (int i = 0; i < booksInArray; i++) {
                    if (strcmp(books[i].Title, searchInput) == 0 || strcmp(books[i].BookID, searchInput) == 0) {
                        found = 1;
                        printf("Book Found:\n");
                        printf("ID: %s\n", books[i].BookID);
                        printf("Title: %s\n", books[i].Title);
                        printf("Author: %s\n", books[i].Author);
                        break;
                    }
                }
                if (!found) {
                    printf("Error: Book with title or ID '%s' not found.\n", searchInput);
                }
                break;
            }
            case '4': {
                if (booksInArray == 0) {
                    printf("No books in the system.\n");
                } else {
                    printf("Books in the system:\n");
                    for (int i = 0; i < booksInArray; i++) {
                        printf("ID: %s, Title: %s, Author: %s\n", books[i].BookID, books[i].Title, books[i].Author);
                    }
                }
                break;
            }
            case '5': {
                printf("Exiting the program. Goodbye!\n");
                exit(0);
                break;
            }
        }
    } while (1);

    return 0;
}
