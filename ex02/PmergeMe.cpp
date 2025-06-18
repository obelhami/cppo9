#include "PmergeMe.hpp"


static void InvalidArguments(char **check)
{
    for(int i = 1; check[i]; i++)
    {
        std::istringstream ss(check[i]);
        std::string token;
        int counter = 0;
        while (ss >> token)
            counter++;
        if (counter > 1)
            throw std::runtime_error("Argument has multiple numbers.");
        for (size_t i = 0; i < token.size(); ++i)
        {
            if (token[0] == '+' && (token[1] >= '1' && token[1] <= '9'))
                i++;
            if (!isdigit(token[i]))
                throw std::runtime_error("Invalid character");
        }
    }
}

void    MergeMe::sorting(char **arguments)
{
    InvalidArguments(arguments);
    std::deque<int> array;
    for(int i = 1; arguments[i]; i++)
    {
        std::istringstream ss(arguments[i]);
        std::string token;
        ss >> token;
        array.push_back(std::atoi(token.c_str()));
        array.push_front(i ); 
    }
    for (std::deque<int>::iterator it = array.begin(); it != array.end(); it++)
    {
        std::cout << "here ===> " << *it << std::endl;
    }
    std::cout  << "size  = " << array.size() << std::endl;

}
