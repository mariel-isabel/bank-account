#pragma once

#include <string>

inline constexpr int START_ACC_NUM = 1000;
inline constexpr double DEFAULT_INTEREST_RATE = 0.03;
inline constexpr double DEFAULT_OVERDRAFT_LIMIT = 500.0;

void clearInputBuffer();
std::string getCurrentDate();