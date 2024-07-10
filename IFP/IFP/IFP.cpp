#include <iostream>
#include <string>
#include"ini_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    parser parser("ini.txt");
    auto value = parser.get_value<int>("Section1");
    std::cout << "Value: " << value << std::endl;
}