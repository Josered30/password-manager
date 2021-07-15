#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> split(std::string value, std::string flag);
std::string find_password(std::string key);
bool save_password(std::string key, std::string value);

#endif