#include <iostream>
#include <string>
#include <stack>
#include <cctype>

double evaluate_expression(const std::string& expression);

int main() {
    std::string expression;

    std::cout << "Enter an expression: ";
    std::cin >> expression;

    double result = evaluate_expression(expression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

double evaluate_expression(const std::string& expression) {
    std::stack<double> values;
    std::stack<char> operators;
    const char* ptr = expression.c_str();

    while (*ptr) {
        if (isdigit(*ptr)) {
            double num = 0;
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ++ptr;
            }
            if (*ptr == '.') {
                ++ptr;
                double frac = 0.1;
                while (isdigit(*ptr)) {
                    num += (*ptr - '0') * frac;
                    frac /= 10;
                    ++ptr;
                }
            }
            values.push(num);
        } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            while (!operators.empty() && 
                  ((operators.top() == '*' || operators.top() == '/') ||
                   ((operators.top() == '+' || operators.top() == '-') && (*ptr == '+' || *ptr == '-')))) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                switch (op) {
                    case '+': values.push(a + b); break;
                    case '-': values.push(a - b); break;
                    case '*': values.push(a * b); break;
                    case '/': values.push(a / b); break;
                }
            }
            operators.push(*ptr);
            ++ptr;
        } else {
            ++ptr;
        }
    }

    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
        }
    }

    return values.top();
}