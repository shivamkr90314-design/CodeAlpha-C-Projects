
#include <stdio.h>

int main() {
    double a, b;
    char op;

    printf("===== BASIC CALCULATOR =====\n");

    printf("Enter first number: ");
    scanf("%lf", &a);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%lf", &b);

    switch (op) {
        case '+':
            printf("Result = %.2lf\n", a + b);
            break;

        case '-':
            printf("Result = %.2lf\n", a - b);
            break;

        case '*':
            printf("Result = %.2lf\n", a * b);
            break;

        case '/':
            if (b != 0)
                printf("Result = %.2lf\n", a / b);
            else
                printf("Error: Division by zero!\n");
            break;

        default:
            printf("Invalid operator!\n");
    }

    return 0;
}
