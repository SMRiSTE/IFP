﻿#include <iostream>
#include <string>
#include"ini_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    parser parser("ini.txt");
    parser.get_vec();
    auto value = parser.get_value<int>("[Section2]");
    std::cout << "Value: " << value << std::endl;
}