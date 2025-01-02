#include <iostream>
using namespace std;
int main() {
    float num1 = 0;
    float num2 = 0;
    char oper = ' ';
    cout << "Welcome to the basic Arithmetic Calculator!\n";
    cout << "Enter an operation in the format: number1 operator number2\n";
    cout << "Supported operators: + (add), - (subtract), * (multiply), / (divide)\n";
    cout << "\nEnter your calculation: ";
    cin >> num1 >> oper >> num2;

    switch (oper) {
        case '+':
            cout << "Result: " << num1 + num2;
            break;

        case '-':
            cout << "Result: " << num1 - num2;
            break;

        case '*':
            cout << "Result: " << num1 * num2;
            break;

        case '/':
            if (num2 != 0) {
                cout << "Result: " << num1 / num2;
            } else {
                cout << "Error : Division by 0 is not allowed";
                exit(0);
            }
            break;

        default:
            cout << "Error : Unsupported operator '"<<oper<<"' Please use +, -, *, or /.";
    }

    return 0;
}
