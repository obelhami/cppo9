#include "RPN.hpp"

void RPN::calculate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;
    std::stack<int> stack;
    while (iss >> token)
    {
        std::cout << token << std::endl;
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
                throw std::runtime_error("Invalid expression");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            if (token == "+")
                stack.push(a + b);
            else if (token == "-")
                stack.push(a - b);
            else if (token == "*")
                stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Division by zero");
                stack.push(a / b);
            }
        }
        else
        {
            for (size_t i = 0; i < token.size(); ++i)
            {
                if (!isdigit(token[i]))
                    throw std::runtime_error("Invalid character");
            }
            stack.push(std::atoi(token.c_str()));
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Invalid expression");
    std::cout << stack.top() << std::endl;
}
