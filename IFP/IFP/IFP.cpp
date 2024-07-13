#include <iostream>
#include <string>
#include"ini_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    parser parser("ini.txt");
    //parser.get_vec();
    try {
        auto value = parser.get_value<int>("Section1");
        std::cout << "Value: " << value << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}