#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>

bool startsWith(const std::string& s) {
    return s[0] == '[';
}

class parser {
private:
    std::map < std::string, std::map<std::string, std::string>> map;
    std::vector<std::string> vec = {};
    std::string filename;

public:
    parser(std::string f_name) {
        this->filename = f_name;
        std::fstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file");
        }
        else {
            std::string str;
            std::string tem_var;
            std::string line;
            std::getline(file, str);
            while (!file.eof()) {
                if (str.empty() || str[0] == ';') {
                    continue;
                }

                else if(str[0] == '[') {
                    std::string sec_name = str;
                    line = str;
                    tem_var = "";
                    while (true) {
                        getline(file, str);
                        tem_var = str;
                        if (!file.eof()) {
                            if (tem_var.empty() || tem_var[0] == ';' || tem_var[0] == ' ') {
                                continue;
                            }
                            else if (tem_var[0] == '[') {
                                sec_name = str;
                                break;
                            }
                            else {
                                std::string tem_var1;
                                for (int i = tem_var.find('=') + 1; i < tem_var.size(); i++) {
                                    if (tem_var[i] == ';') {
                                        break;
                                    }
                                    tem_var1 += tem_var[i];
                                }

                                try {
                                    int num = stoi(tem_var1);
                                    map[sec_name] = std::map<std::string, std::string>{ {"Int", tem_var1} };
                                }
                                catch (const std::invalid_argument&) {
                                    if (tem_var1.empty()) {
                                        continue;
                                    }
                                    map[sec_name] = std::map<std::string, std::string>{ {"String", tem_var1} };
                                    continue;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
    }

    void get_vec() {
        if (map["[Section2]"]["Int"].empty()) {
            std::cout << "lalala";
        }
    }

    template<class T>
    T get_value(std::string sec_name) {
        return 0;
    }

    template<>
    int get_value(std::string sec_name) {
        return 0;
    }
};