#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdexcept>

bool startsWith(const std::string& s) {
    return s[0] == '[';
}

class parser {
private:
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
            while (std::getline(file, str)) {
                if (str.empty() || str[0] == ';') {
                    continue;
                }
                else {
                    this->vec.push_back(str);
                }
            }
        }
    }

    void get_vec() {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i] << "\n";
        }
    }

    template<class T>
    T get_value(std::string sec_name) {
        return 0;
    }

    template<>
    int get_value(std::string sec_name) {
        if (vec.size() == 0) {
            throw std::runtime_error("Value not found");
        }
        std::vector<std::string> sec_vec = {};

        int sec_begin = -1;
        int sec_end = -1;
        std::string variable_str;
        int i = 0;
        while (i < vec.size()) {
            if (vec[i] == "[" + sec_name + "]") {
                sec_begin = i;
                
                for (int j = i + 1; j < vec.size(); j++) {
                    variable_str = vec[j];
                    if (variable_str.find('[') != std::string::npos || j == vec.size() - 1) {
                        sec_end = j;
                        i = j;
                        break;
                    }
                }
            } 
            else {
                i++;
            }
        }
        std::cout << sec_begin << " " << sec_end << "\n";
        if (sec_begin == -1 || sec_end == -1) {
            throw std::runtime_error("Section not found");
        }

        for (int i = sec_begin + 1; i < sec_end + 1; i++) {
            if (vec[i].empty() || vec[i][0] == ';') {
                continue;
            }
            else {
                sec_vec.push_back(vec[i]);
            }
        }

        for (int i = 0; i < sec_vec.size(); i++) {
            std::cout << sec_vec[i] << " ";
        }

        std::string str;
        std::string str1;
        for (int i = 0; i < sec_vec.size(); i++) {
            str = sec_vec[i];
            for (int j = str.find('=') + 1; j < str.size(); j++) {
                if (str[j] == ';') {
                    break;
                }
                else if (str[j] == '[') {
                    break;
                }
                else {
                    str1 += str[j];
                }
            }
            sec_vec[i] = str1;
            str1 = "";
        }

        for (int i = 0; i < sec_vec.size(); i++) {
            std::cout << sec_vec[i] << " ";
        }

        for (int i = 0; i < sec_vec.size(); i++) {
            if (sec_vec[i].empty()) {
                sec_vec.erase(sec_vec.begin() + i);
                i--;
            }
        }

        if (sec_vec.empty()) {
            throw std::runtime_error("Value not found");
        }

        for (int i = 0; i < sec_vec.size(); i++) {
            try {
                int num = std::stoi(sec_vec[i]);
                std::cout << num << std::endl;
                return num;
            }
            catch (const std::invalid_argument&) {
                continue;
            }
        }
        throw std::runtime_error("Value not found");
    }
};