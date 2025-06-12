#pragma once

#include <fstream>
#include <map>
#include <iostream>
#include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, double> btcData;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& object);
        BitcoinExchange &operator=(const BitcoinExchange& object);
        ~BitcoinExchange();
        void    CheckFile_Input(std::string File_Name);
};