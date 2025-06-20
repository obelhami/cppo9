#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>
#include <utility>
#include <vector>


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
            if (token[0] == '+' && (token[1] >= '0' && token[1] <= '9'))
                i++;
            else if (!isdigit(token[i]))
                throw std::runtime_error("Invalid character");
        }
    }
}
// static std::deque<std::pair<int, int> > fillContainer(std::deque<int> &array)
// {
//     std::deque<std::pair<int, int> > pairs;
//     for (size_t i = 0; i + 1 < array.size(); i+=2)
//     {
//         std::pair<int, int> fill = std::make_pair(array[i], array[i + 1]);
//         pairs.push_back(fill);
//     }
//     return pairs;
// }

template<typename Container>
static std::deque<std::pair<int,int> > fillPairs(Container &array)
{
    std::deque<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < array.size(); i += 2)
        pairs.push_back(std::make_pair(array[i], array[i+1]));
    return pairs;
}

// static std::vector<std::pair<int, int> > fillContainer(std::vector<int> &array) {
//     std::vector<std::pair<int, int> > pairs;
//     for (size_t i = 0; i + 1 < array.size(); i += 2)
//         pairs.push_back(std::make_pair(array[i], array[i + 1]));
//     return pairs;
// }

template<typename Container>
static void printContainer(const Container &c, const char *msg)
{
    std::cout << msg;
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

static bool compare(std::pair<int, int> a, std::pair<int, int> b)
{
    return a.first < b.first;
}

static std::deque<size_t> generateJacobsthalOrder(size_t size)
{
    std::deque<size_t> jacob;
    if (size == 0)
        return jacob;

    jacob.push_back(0); // a(0) = 0
    if (size == 1)
        return jacob;

    jacob.push_back(1); // a(1) = 1

    size_t a = 0, b = 1;
    while (true)
    {
        size_t next = b + 2 * a;
        if (next >= size)
            break;
        jacob.push_back(next);
        a = b;
        b = next;
    }

    // Now generate full insertion order like Ford-Johnson requires:
    std::deque<bool> inserted(size, false);
    std::deque<size_t> order;

    for (size_t i = 1; i < jacob.size(); ++i)
    {
        size_t idx = jacob[i];
        if (idx < size && !inserted[idx])
        {
            order.push_back(idx);
            inserted[idx] = true;
        }

        for (int j = idx - 1; j >= 0; --j)
        {
            if (!inserted[j])
            {
                order.push_back(j);
                inserted[j] = true;
            }
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        if (!inserted[i])
            order.push_back(i);
    }

    return order;
}


static void BinaryInsert(std::deque<int> &chain, int value)
{
    std::deque<int>::iterator it = std::lower_bound(chain.begin(), chain.end(), value);
    chain.insert(it, value);
}

template <typename Container>
static void mergeInsertSort(Container &array)
{
    int struggle = -1;
    if (array.size() % 2 != 0)
    {
        struggle = array.back();
        array.pop_back();
    }

    std::deque<std::pair<int, int> > pairs = fillPairs(array);
    for(size_t i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }

    std::sort(pairs.begin(), pairs.end(), compare);

    std::deque<int> largest;
    std::deque<int> lowest;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        largest.push_back(pairs[i].first);
        lowest.push_back(pairs[i].second);
    }

    largest.insert(largest.begin(), lowest.front());
    lowest.erase(lowest.begin());

    std::deque<size_t> order = generateJacobsthalOrder(lowest.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        int val = lowest[order[i]];
        BinaryInsert(largest, val);
    }

    if (struggle != -1)
        BinaryInsert(largest, struggle);

    // Update original container with sorted results
    array.clear();
    for (size_t i = 0; i < largest.size(); i++)
        array.push_back(largest[i]);
}


void    MergeMe::sorting(char **arguments)
{
    InvalidArguments(arguments);
    std::deque<int> array;
    std::vector<int> array2;
    for(size_t i = 1; arguments[i]; i++)
    {
        std::istringstream ss(arguments[i]);
        std::string token;
        ss >> token;
        array.push_back(std::atoi(token.c_str()));
        array2.push_back(std::atoi(token.c_str()));

    }

    printContainer(array, "Before: ");

    clock_t startDeq = clock();
    mergeInsertSort(array);
    clock_t endDeq = clock();

    clock_t startVec = clock();
    mergeInsertSort(array2);
    clock_t endVec = clock();

    printContainer(array, "After: ");

    double timeDeq = static_cast<double> (endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;
    double timeVec = static_cast<double> (endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;

        std::cout << "Time to process a range of " << array.size()
                  << " elements with std::deque : " << timeVec << " us" << std::endl;
        std::cout << "Time to process a range of " << array2.size()
                  << " elements with std::vector  : " << timeDeq << " us" << std::endl;
}


