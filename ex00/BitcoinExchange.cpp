#include "BitcoinExchange.hpp"
#include <string>

BitcoinExchange::BitcoinExchange()
{
    std::ifstream file("data.csv");
    if (file.is_open()) 
    {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string date;
            std::string valueStr;
            if (std::getline(ss, date, ',') && std::getline(ss, valueStr)) {
                std::stringstream converter(valueStr);
                double price;
                converter >> price; // Convert to double
                btcData[date] = price;
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "there is an error in opening the file " << std::endl;
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& object)
{
    this->btcData = object.btcData;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& object)
{
    if (this != &object)
    {
        this->btcData = object.btcData;
    }
    return *this;
}


static bool isValidDate(const std::string& date)
{
    // Check format: length and dashes
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    // Check all digits
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    // Parse year, month, day
    int year  = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day   = atoi(date.substr(8, 2).c_str());

    // Check valid month
    if (month < 1 || month > 12)
        return false;

    // Days per month
    int maxDay = 31;
    if (month == 2)
    {
        // Leap year check
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        maxDay = isLeap ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDay = 30;

    if (day < 1 || day > maxDay)
        return false;

    return true;
}



static std::string trim(std::string str)
{
    // Remove leading whitespace
    while (!str.empty() && (str[0] == ' ' || str[0] == '\t' || str[0] == '\n' || str[0] == '\r'))
        str.erase(0, 1);

    // Remove trailing whitespace
    while (!str.empty() && (str[str.size() - 1] == ' ' || str[str.size() - 1] == '\t' || str[str.size() - 1] == '\n' || str[str.size() - 1] == '\r'))
        str.erase(str.size() - 1, 1);

    return str;
}



void    BitcoinExchange::CheckFile_Input(std::string File_Name)
{
    std::ifstream input_file(File_Name);
    if (input_file.is_open())
    {
        std::string line;
        std::getline(input_file, line);
        while (std::getline(input_file, line))
        {
            std::stringstream ss(line);
            std::string date;
            std::string valueStr;
            if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
            {
                date = trim(date);
                valueStr = trim(valueStr);
                if (!isValidDate(date)) {
                    std::cerr << "Error: invalid date => " << date << std::endl;
                    continue;
                }
                double value;
                std::stringstream valuefile(valueStr);
                valuefile >> value;
                if (value < 0)
                {
                    std::cerr << "Error: not a positive number." << std::endl;
                    continue;
                }

            }
        }
    }
}
