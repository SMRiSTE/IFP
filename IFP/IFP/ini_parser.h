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
			while(std::getline(file,str)){
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
	int get_value(std::string sec_name){
		if (vec.size() == 0) {
			throw std::runtime_error("Value not found");
		}
		std::vector<std::string> sec_vec = {};
		auto it = std::find(vec.begin(), vec.end(), "[" + sec_name + "]");
		int sec_begin = static_cast<int>(std::distance(vec.begin(),it));
		int sec_end = 0;
		for (int i = sec_begin + 1; i < vec.size(); i++) {
			auto it1 = std::find_if(it + 1, vec.end(), startsWith);
			sec_end = static_cast<int>(std::distance(it, it1)) + sec_begin;
		}

		for (int i = sec_begin + 1; i < sec_end; i++) {
			if (vec[i].empty()) {
				continue;
			}
			else {
				sec_vec.push_back(vec[i]);
			}
		}
		
		std::string str;
		std::string str1;
		for (int i = 0; i < sec_vec.size(); i++) {
			str = sec_vec[i];
			for (int j = sec_vec[i].find('=') + 1; j < sec_vec[i].size(); j++) {
				str1 += str[j];
			}
			sec_vec[i] = str1;
			str1 = " ";
		}

		for (int i = 0; i < sec_vec.size(); i++) {
			int num = std::stoi(sec_vec[i]);
			if (num) {
				return num;
			}
			else {
				continue;
			}
		}
		throw std::runtime_error("Value not found");
	}
};