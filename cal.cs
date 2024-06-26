using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        Console.Write("Enter an expression: ");
        string expression = Console.ReadLine();

        double result = EvaluateExpression(expression);
        Console.WriteLine("Result: " + result);
    }

    static double EvaluateExpression(string expression)
    {
        Stack<double> values = new Stack<double>();
        Stack<char> operators = new Stack<char>();
        int i = 0;

        while (i < expression.Length)
        {
            if (char.IsDigit(expression[i]))
            {
                double num = 0;
                while (i < expression.Length && char.IsDigit(expression[i]))
                {
                    num = num * 10 + (expression[i] - '0');
                    i++;
                }
                if (i < expression.Length && expression[i] == '.')
                {
                    i++;
                    double frac = 0.1;
                    while (i < expression.Length && char.IsDigit(expression[i]))
                    {
                        num += (expression[i] - '0') * frac;
                        frac /= 10;
                        i++;
                    }
                }
                values.Push(num);
            }
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
            {
                while (operators.Count > 0 &&
                      ((operators.Peek() == '*' || operators.Peek() == '/') ||
                       ((operators.Peek() == '+' || operators.Peek() == '-') && (expression[i] == '+' || expression[i] == '-'))))
                {
                    double b = values.Pop();
                    double a = values.Pop();
                    char op = operators.Pop();
                    switch (op)
                    {
                        case '+': values.Push(a + b); break;
                        case '-': values.Push(a - b); break;
                        case '*': values.Push(a * b); break;
                        case '/': values.Push(a / b); break;
                    }
                }
                operators.Push(expression[i]);
                i++;
            }
            else
            {
                i++;
            }
        }

        while (operators.Count > 0)
        {
            double b = values.Pop();
            double a = values.Pop();
            char op = operators.Pop();
            switch (op)
            {
                case '+': values.Push(a + b); break;
                case '-': values.Push(a - b); break;
                case '*': values.Push(a * b); break;
                case '/': values.Push(a / b); break;
            }
        }

        return values.Peek();
    }
}