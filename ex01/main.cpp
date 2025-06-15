#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Your program must be one argument for example ./RPN '8 9 * 9 - 9 - 9 - 4 - 1 +'" << std::endl;
        return 1;
    }
}