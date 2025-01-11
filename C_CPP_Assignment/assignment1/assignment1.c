#include <stdio.h>
#include <stdlib.h>
int main(){
    float num1 = 0, num2 = 0;
    char oper = ' ';
    float result = 0;
    int valid = 1;

    printf("Welcome to the basic Arithmetic Calculator!\n");
    printf("Enter an operation in the format: number1 operator number2\n");
    printf("Supported operators: + (add), - (subtract), * (multiply), / (divide)\n");
    printf("\nEnter your calculation: ");
    scanf("%f %c %f", &num1, &oper, &num2);

    switch (oper)
    {
    case '+':
    result = num1 + num2;
    break;

    case '-':
    result = num1 - num2;
    break;

    case '*':
    result = num1 * num2;
    break;

    case '/':
    if (num2 != 0){
        result = num1 / num2;
        break;
    }else{
        printf("Error : Division by 0 is not allowed\n");
        valid = 0;
        exit(0);
    }
    
    default:
    printf ("Error : Unsupported operator '%c'", oper);
    printf("Please use +, -, *, or /.\n");
    valid = 0;
    break;
    }

    if (valid == 1){
        printf ("Result: %.2f", result);
    }

    return 0;
}