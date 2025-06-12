#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        std::cout << "error\n";
        return 1;
    }
    BitcoinExchange bitcoin;
    bitcoin.CheckFile_Input(av[1]);
}