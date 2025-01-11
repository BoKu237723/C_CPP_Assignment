#include <iostream>
#include <fstream>
#include <cstring>
#include <limits> // numeric_limits<streamsize

#define FILENAME "dictionary.txt"
#define MAX_WORDNAME 10
#define MAX_DEFINITION 1000
#define LINE_SIZE (MAX_WORDNAME + MAX_DEFINITION)

using namespace std;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32; // Convert to lowercase
        }
    }
}

void addWord() {
    char word[MAX_WORDNAME], definition[MAX_DEFINITION];

    cout << "Enter word: ";
    cin.getline(word, MAX_WORDNAME);

    cout << "Enter definition: ";
    cin.getline(definition, MAX_DEFINITION);

    ofstream outFile(FILENAME, ios::app);
    if (outFile.is_open()) {
        outFile << word << "|" << definition << "\n";
        cout << "Word added successfully!\n\n";
    } else {
        cout << "Error\n\n";
    }
}

// void displayWords() {
//     ifstream inFile(FILENAME);
//     char line[LINE_SIZE];

//     cout << "\nWord                         Definition\n";
//     cout << "-------------------------------------------------------\n";
//     if (inFile.is_open()) {
//         while (inFile.getline(line, LINE_SIZE)) {
//             char word[MAX_WORDNAME], definition[MAX_DEFINITION];
//             sscanf(line, "%10[^|]|%999[^\n]", word, definition);
//             cout << word << "                 " << definition << "\n";
//         }
//         cout << "\n";
//     } else {
//         cout << "Error opening file for reading.\n";
//     }
// }

void displayWords() {
    ifstream inFile(FILENAME);
    char line[LINE_SIZE];

    // Header
    cout << "\nWord               Definition\n";
    cout << "---------------------------------\n";

    if (inFile.is_open()) {
        while (inFile.getline(line, LINE_SIZE)) {
            char word[MAX_WORDNAME], definition[MAX_DEFINITION];
            sscanf(line, "%10[^|]|%999[^\n]", word, definition);
            cout << word;
            for (int i = strlen(word); i < 18; i++){
                cout << " "; 
            }
            
            cout << definition << "\n";
        }
        cout << "\n";
    } else {
        cout << "Error\n\n";
    }
}

void searchWord() {
    char search[MAX_WORDNAME];
    cout << "Enter the word to search: ";
    cin.getline(search, MAX_WORDNAME);
    toLowerCase(search);

    ifstream inFile(FILENAME);
    if (inFile.is_open()) {
        char line[LINE_SIZE];
        bool found = false;
        while (inFile.getline(line, LINE_SIZE)) {
            char word[MAX_WORDNAME], definition[MAX_DEFINITION];
            sscanf(line, "%10[^|]|%999[^\n]", word, definition);

            char tempWord[MAX_WORDNAME];
            strncpy(tempWord, word, MAX_WORDNAME);
            toLowerCase(tempWord);

            if (strcmp(tempWord, search) == 0) {
                cout << "Definition: " << definition << "\n\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Word not found.\n\n";
        }
    } else {
        cout << "Error opening file.\n\n";
    }
}

void deleteWord() {
    char target[MAX_WORDNAME];
    cout << "Enter the word to delete: ";
    cin.getline(target, MAX_WORDNAME);
    toLowerCase(target);

    ifstream inFile(FILENAME);
    if (!inFile.is_open()) {
        cout << "Error\n\n";
        return;
    }

    char tempStorage[100][LINE_SIZE];
    int count = 0, found = 0;

    while (inFile.getline(tempStorage[count], LINE_SIZE)) {
        char word[MAX_WORDNAME], definition[MAX_DEFINITION];
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
    inFile.close();

    if (found) {
        ofstream outFile(FILENAME, ios::trunc);
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << tempStorage[i];
            }
            cout << "Word '"<< target <<"' successfully deleted successfully.\n\n";
        } else {
            cout << "Error\n\n";
        }
    } else {
        cout << "Word not found.\n\n";
    }
}

void updateDefinition() {
    char target[MAX_WORDNAME];
    char newDefinition[MAX_DEFINITION];
    cout << "Enter the word to update: ";
    cin.getline(target, MAX_WORDNAME);
    toLowerCase(target);

    ifstream inFile(FILENAME);
    if (!inFile.is_open()) {
        cout << "Error\n\n";
        return;
    }

    char tempStorage[100][LINE_SIZE];
    int count = 0, found = 0;

    while (inFile.getline(tempStorage[count], LINE_SIZE)) {
        char word[MAX_WORDNAME], definition[MAX_DEFINITION];
        sscanf(tempStorage[count], "%10[^|]|%999[^\n]", word, definition);

        char tempWord[MAX_WORDNAME];
        strncpy(tempWord, word, MAX_WORDNAME);
        toLowerCase(tempWord);

        if (strcmp(tempWord, target) == 0) {
            found = 1;
            cout << "Enter new definition: ";
            cin.getline(newDefinition, MAX_DEFINITION);
            snprintf(tempStorage[count], LINE_SIZE, "%s|%s\n", word, newDefinition);
        }
        count++;
    }
    inFile.close();

    if (found) {
        ofstream outFile(FILENAME, ios::trunc);
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << tempStorage[i];
            }
            cout << "Updated successfully.\n\n";
            return;
        } else {
            cout << "Error\n\n";
        }
    } else {
        cout << "Word not found.\n\n";

    }
}


int main() {
    char choice;
    do {
        ifstream myFile(FILENAME);
        if(!myFile.is_open()){
            ofstream file(FILENAME);
            if(file.is_open()){
                cout << "No existing dictionary file found. Starting fresh.\n\n";
                file.close();
            }
        }
        cout << "Dictionary Application";
        cout << "\n1. Add Word\n2. Display Words\n3. Search Word\n4. Delete Word\n5. Update Definition\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        clearInput();

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
                cout << "Invalid choice. Please choose a valid option.\n";
        }
    } while (choice != '6');
    return 0;
}