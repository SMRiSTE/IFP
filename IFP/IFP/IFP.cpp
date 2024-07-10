#include <iostream>
#include <string>
#include"ini_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    try {
        parser parser("ini.txt");
        int value = parser.get_value<int>("Section4");
        std::cout << "Value: " << value << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}