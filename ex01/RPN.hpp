#pragma once

#include <iostream>
#include <stack>
#include <cstdlib>

class Rnp
{
    private:
        static std::stack<std::string> rnp;
    public:
        Rnp();
        Rnp(const Rnp &object);
        Rnp &operator=(const Rnp &object);
        ~Rnp();
       static void    ParsingInput(std::string string);
       static void    CalculationMethod(std::string string);
};