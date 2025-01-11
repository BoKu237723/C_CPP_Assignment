#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    char choice;
    do {
        cout << "\nContact Management System\n1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display All Contacts\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                string name;
                string phone;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Phone Number: ";
                cin >> phone;
                ofstream myFile("contacts.txt", ios::app);
                if (myFile.is_open()) {
                    myFile << name << ","<< phone << endl;
                    myFile.close();
                    cout << "Contact added successfully..\n";
                } else {
                    cout << "Error: Could not open file.\n";
                }
                break;
            }
            case '2': {
                string search;
                cout << "Enter name to search: ";
                cin >> search;

                ifstream myFile("contacts.txt");
                if (myFile.is_open()) {
                    string line;
                    bool found = false;
                    while (getline(myFile, line)) {
                        if (line.find(search) != string::npos) {
                            cout << "Contact found: " << line << endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "No contact found with that name.\n";
                    }
                    myFile.close();
                } else {
                    cout << "Error: Could not open file.\n";
                }
                break;
            }
            case '3': {
                string deleteContact;
                cout << "Enter name to delete: ";
                cin >> deleteContact;
                ifstream myFile("contacts.txt");
                ofstream tempFile("temp.txt"); 

                if (myFile.is_open() && tempFile.is_open()) {
                    string line;
                    bool deleted = false;
                    while (getline(myFile, line)) {
                        if (line.find(deleteContact) == string::npos) {
                            tempFile << line << endl; 
                        } else {
                            deleted = true; 
                        }
                    }
                    myFile.close();
                    tempFile.close();
                    if (deleted) {
                        remove("contacts.txt"); 
                        rename("temp.txt", "contacts.txt");  
                        cout << "Contact deleted successfully..\n";
                    } else {
                        cout << "Contact not found.\n";
                    }
                } else {
                    cout << "Error: Could not open file.\n";
                }
                break;
            }

            case '4': {
                ifstream myFile("contacts.txt");
                if (myFile.is_open()) {
                    string line;
                    cout << "Contact List:\n";
                    cout << "===========================\n";
                    while(getline(myFile, line)){
                        stringstream ss(line);
                        string name, phone;
                        getline(ss,name, ','); //finds cor
                        getline(ss,phone);

                        cout << "Name: " << name << endl;
                        cout << "Phone: " << phone << endl;
                    }
                    cout << "\n===========================\n";
                    myFile.close();
                } else {
                    cout << "Error: Could not open file.\n";
                }
                break;
            }
            case '5': {
                exit(0);
            }
            default:
                cout << "Error: Invalid choice!\n";
        }
    } while (choice != '5');

    return 0;
}

