#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error\n";
        return 1;
    }
    MergeMe::sorting(av[1]);
}