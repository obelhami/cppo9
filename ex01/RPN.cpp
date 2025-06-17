#include "RPN.hpp"

std::stack<std::string> Rnp::rnp; // <<< This is the missing definition!

Rnp::Rnp()
{}

Rnp::Rnp(const Rnp &object)
{
    *this = object;
}

Rnp &Rnp::operator=(const Rnp &object)
{
    if (this != &object)
    {
            this->rnp = object.rnp;
    }
    return *this;
}

Rnp::~Rnp()
{}


static bool isValidExpression(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (!(isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == ' ')) {
            return true;
        }
    }
    return false;
}

void    Rnp::ParsingInput(std::string string)
{
    std::cout << string<< std::endl;

    if (isValidExpression(string) == true)
    {
        std::cout << "the argument has a character/n";
        exit(1);
    }
    CalculationMethod(string);
}

void    Rnp::CalculationMethod(std::string string)
{
    while ( )
}