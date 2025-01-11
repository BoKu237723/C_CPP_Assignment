#include <iostream>
// #include <time.h>
#include <ctime>
using namespace std;
int main(){
    int start, end;
    cout << "Welcome to the Multiplication Game!\n";
    cout << "You have 6 seconds to answer each question. Let's start!\n\n";

    int a,b, systemAnswer, userAnswer;

    while(true){
        srand(time(0));
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        systemAnswer = a*b;
        cout << "What is " << a << " * " << b << "? ";
        start = time(0);
        cin >> userAnswer;

        end = time(0); //NULl
        if(end - start > 6){
            cout <<"Times up!";
            break;
        }else if(systemAnswer == userAnswer){
            cout << "Correct!\n";
        }else{
            cout << "Wrong! The correct answer was " << systemAnswer << endl;
            break;
        }
    }
    return 0;
}
