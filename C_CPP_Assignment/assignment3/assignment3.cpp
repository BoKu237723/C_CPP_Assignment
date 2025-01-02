#include <iostream>
#include <string>
using namespace std;

struct Book {
    string BookID;
    string Title;
    string Author;
};

int main() {
    Book books[1000];
    int booksInArray = 0;
    string choice;

    do {
        cout << "\nBook Management System \n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Search Book\n";
        cout << "4. Display All Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice.length() != 1 || choice[0] < '1' || choice[0] > '5') {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        switch (choice[0]) {
            case '1': {
                if (booksInArray >= 1000) {
                    cout << "Book array is full!\n";
                    break;
                }
                Book newBook;
                cout << "Enter Book ID: ";
                cin >> newBook.BookID;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, newBook.Title);
                cout << "Enter Author Name: ";
                getline(cin, newBook.Author);

                books[booksInArray++] = newBook;
                cout << "Book added successfully.\n";
                break;
            }
            case '2': {
                string bookID;
                cout << "Enter Book ID to delete: ";
                cin >> bookID;

                bool found = false;
                for (int i = 0; i < booksInArray; i++) {
                    if (books[i].BookID == bookID) {
                        found = true;
                        for (int j = i; j < booksInArray - 1; j++) {
                            books[j] = books[j + 1];
                        }
                        booksInArray--;
                        cout << "Book with ID '"<< bookID << "' deleted successfully.\n";
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: Book with ID '"<< bookID <<"' not found.\n";
                }
                break;
            }
            case '3': {
                string searchTitle;
                cout << "Enter Book Title to search: ";
                cin.ignore();
                getline(cin, searchTitle);

                bool found = false;
                for (int i = 0; i < booksInArray; i++) {
                    if (books[i].Title == searchTitle) {
                        found = true;
                        cout << "Book Found:\n";
                        cout << "ID: " << books[i].BookID << "\n";
                        cout << "Title: " << books[i].Title << "\n";
                        cout << "Author: " << books[i].Author << "\n";
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: Book with title '" << searchTitle << "' not found.\n";
                }
                break;
            }
            case '4': {
                if (booksInArray == 0) {
                    cout << "No books in the system.\n";
                } else {
                    cout << "Books in the system:\n";
                    for (int i = 0; i < booksInArray; i++) {
                        cout << "ID: " << books[i].BookID << ", Title: " << books[i].Title << ", Author: " << books[i].Author << "\n";
                    }
                }
                break;
            }
            case '5':
                exit(0);
        }
    } while (true);

    return 0;
}
