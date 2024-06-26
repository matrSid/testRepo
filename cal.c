#include <stdio.h>
#include <stdlib.h>

double evaluate_expression(const char* expression);

int main() {
    char expression[100];

    printf("Enter an expression: ");
    scanf("%s", expression);

    double result = evaluate_expression(expression);
    printf("Result: %lf\n", result);

    return 0;
}

double evaluate_expression(const char* expression) {
    char operators[100];
    double values[100];
    int op_top = -1, val_top = -1;
    const char* ptr = expression;

    while (*ptr) {
        if (*ptr >= '0' && *ptr <= '9') {
            double num = 0;
            while (*ptr >= '0' && *ptr <= '9') {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            if (*ptr == '.') {
                ptr++;
                double frac = 0.1;
                while (*ptr >= '0' && *ptr <= '9') {
                    num += (*ptr - '0') * frac;
                    frac /= 10;
                    ptr++;
                }
            }
            values[++val_top] = num;
        } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            while (op_top != -1 && 
                  ((operators[op_top] == '*' || operators[op_top] == '/') ||
                   ((operators[op_top] == '+' || operators[op_top] == '-') && (*ptr == '+' || *ptr == '-')))) {
                double b = values[val_top--];
                double a = values[val_top--];
                char op = operators[op_top--];
                switch (op) {
                    case '+': values[++val_top] = a + b; break;
                    case '-': values[++val_top] = a - b; break;
                    case '*': values[++val_top] = a * b; break;
                    case '/': values[++val_top] = a / b; break;
                }
            }
            operators[++op_top] = *ptr;
            ptr++;
        } else {
            ptr++;
        }
    }

    while (op_top != -1) {
        double b = values[val_top--];
        double a = values[val_top--];
        char op = operators[op_top--];
        switch (op) {
            case '+': values[++val_top] = a + b; break;
            case '-': values[++val_top] = a - b; break;
            case '*': values[++val_top] = a * b; break;
            case '/': values[++val_top] = a / b; break;
        }
    }

    return values[val_top];
}