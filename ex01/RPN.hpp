#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

class RPN {
public:
    static void calculate(const std::string &expression);
};

#endif
