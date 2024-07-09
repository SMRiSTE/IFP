#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class parser {
private:
	std::string filename;

public:
	parser(std::string f_name) {
		this->filename = f_name;
	}

	template<class T>
	T get_value(std::string sec_name) {
		setlocale(LC_ALL, "Russian");

		std::fstream file(filename);
		if (!file) {
			throw std::runtime_error("Unable to open file");
		}
		else {
			std::string str;
			std::string temp = " ";
			while (str != sec_name) {
				std::getline(file, str);
				str.erase(str.begin());
				str.pop_back();
				
			}

			std::vector<std::string> vec = {};
			while(true){
				std::getline(file, str);
				if (str.empty() || str[0] == ';') {
					continue;
				}

				else if(str[0] == '[') {
					break;
				}

				else {
					vec.push_back(str);
				}
			}
			
			std::string str1;
			for (int i = 0; i < vec.size(); i++) {
				str = vec[i];
				for (int j = vec[i].find('=') + 1; j < vec[i].size(); j++) {
					str1 += str[j];
				}
				vec[i] = str1;
				str1 = " ";
			}

			for (int i = 0; i < vec.size(); i++) {
				std::cout << vec[i] << "\n";
			}
			
			return 0;
			
			
		}

	}

	
};