#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int main() {
    int choice = 0;
    string inputFile, outputFile;
    int key = 0;

    cout << "Simple File Encryption/Decryption Program" << endl;
    cout << "1. Encrypt a file" << endl;
    cout << "2. Decrypt a file" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the input file name: ";
        cin >> inputFile;
        ifstream input(inputFile); //check
        if (!input) {
            cout << "File does not exist." << endl;
            exit(0);
        } else {
            cout << "Enter the output file name: ";
            cin >> outputFile;
            cout << "Enter the key (integer): ";
            cin >> key;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                cout << "Invalid input. Please enter a valid integer." << endl;
                exit(0);
            }else{
                string storage;
                char ch;
                while (input.get(ch)) {
                    storage += (ch + key);  
                }
                input.close();

                ofstream output(outputFile);
                if (!output) {
                    cout << "Error in handling output file." << endl;
                    exit(0);
                } else {
                    output << storage;  //write from storage
                    cout << "Encryption completed. Output saved to '" << outputFile << "'." << endl;
                    output.close();
                }
            }
        }
    } else if (choice == 2) {
        cout << "Enter the input file name: ";
        cin >> inputFile;
        ifstream input(inputFile);
        if (!input) {
            cout << "File does not exist." << endl;
            exit(0);
        } else {
            cout << "Enter the output file name: ";
            cin >> outputFile;
            cout << "Enter the key (integer): ";
            cin >> key;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                cout << "Invalid input. Please enter a valid integer." << endl;
                exit(0);
            }else{
                string storage;
                char ch;
                while (input.get(ch)) {
                    storage += (ch - key);  
                }
                input.close();

                ofstream output(outputFile);
                if (!output) {
                    cout << "Error in handling output file." << endl;
                    exit(0);
                } else {
                    output << storage;  //write from storage
                    cout << "Decryption completed. Output saved to '" << outputFile << "'." << endl;
                    output.close();
                }
            }
        }
    } else {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
    }

    return 0;
}







// #include <iostream>
// #include <limits> 

// int main() {
//     int userInput;

//     std::cout << "Please enter an integer: ";
//         std::cin >> userInput;

//         // Check if the input is a valid integer
//         if (std::cin.fail()) {
//             std::cin.clear(); // Clear the error flag
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
//             std::cout << "Invalid input. Please enter a valid integer.\n";
//         } else {
//             std::cout << "You entered the integer: " << userInput << std::endl;
//         }

//     return 0;
// }
