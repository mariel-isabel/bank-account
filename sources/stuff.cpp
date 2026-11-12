#include "stuff.hpp"

#include <ctime>
#include <iostream>
#include <limits>

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getCurrentDate()
{
    const std::time_t now = std::time(nullptr);
    const char* currentDate = std::ctime(&now);
    if (currentDate == nullptr)
    {
        return {};
    }

    std::string date(currentDate);
    if (!date.empty() && date.back() == '\n')
    {
        date.pop_back();
    }
    return date;
}