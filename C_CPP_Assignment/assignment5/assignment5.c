#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    int start, end;
    printf("Welcome to the Multiplication Game!\n");
    printf("You have 6 seconds to answer each question. Let's start!\n\n");

    int a,b, systemAnswer, userAnswer;

    while(1){ //true
        srand(time(NULL));
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        systemAnswer = a*b;
        printf ("What is %d * %d? ", a, b);
        start = time(NULL);
        scanf("%d", &userAnswer);

        end = time(NULL);
    
        if (end - start > 6){
            printf("Times up!");
            break;
        }else if (systemAnswer == userAnswer){
            printf("Correct!\n");
        }else{
            printf("Wrong! The correct answer was %d.", systemAnswer);
            break;
        }
    }
    return 0;
}