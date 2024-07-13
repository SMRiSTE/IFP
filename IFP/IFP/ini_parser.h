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
    std::map < std::string, std::map<int, std::string>> map;
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
            int index;
            while (!file.eof()) {
                index = 0;
                if (str.empty() || str[0] == ';') {
                    continue;
                }

                else if(str[0] == '[') {
                    std::string sec_name = str;
                    line = str;
                    tem_var = "";
                    while (!file.eof()) {
                        getline(file, str);
                        tem_var = str;
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
                                    else if (tem_var[i] == ' ') {
                                        continue;
                                    }
                                    tem_var1 += tem_var[i];
                                }
                                if (!map.count(sec_name)) {
                                    map[sec_name] = std::map<int, std::string>{ {index , tem_var1} };
                                }

                                map[sec_name][index] = tem_var1;
                            }
                            index++;
                    }
                }
            }
        }
    }

    int get_vec() {
        for (int i = map["[Section1]"].size() - 1; i > -1; i--) {
            std::cout << map["[Section1]"][i];
        }
        return 0;
    }

    template<class T>
    T get_value(std::string sec_name) {
        return 0;
    }

    template<>
    int get_value(std::string sec_name) {
        sec_name = "[" + sec_name + "]";
        if (!map.count(sec_name)) {
            throw std::runtime_error("Section not found");
        }

        for (int i = 0; i < map[sec_name].size(); i++) {
            if (map[sec_name][i].empty()) {
                continue;
            }
            else {
                try {
                    int num = std::stoi(map[sec_name][i]);
                    return num;
                }
                catch (const std::invalid_argument&) {
                    continue;
                }
            }
        }

        throw std::runtime_error("Value not found in section");
    }

    template<>
    std::string get_value(std::string sec_name) {
        sec_name = "[" + sec_name + "]";
        if (!map.count(sec_name)) {
            throw std::runtime_error("Section not found");
        }

        for (int i = 0; i < map[sec_name].size(); i++) {
            if (map[sec_name][i].empty()) {
                continue;
            }
            else {
                try {
                    int num = std::stoi(map[sec_name][i]);
                    continue;
                }
                catch (const std::invalid_argument&) {
                    return map[sec_name][i];
                }
            }
        }

        throw std::runtime_error("Value not found in section");
    }
};