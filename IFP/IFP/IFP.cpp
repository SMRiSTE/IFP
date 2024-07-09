#include <iostream>
#include <string>
#include"ini_parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    parser pa("ini.txt");
    pa.get_value<int>("Section2");
}