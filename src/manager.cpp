#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> split(std::string value, std::string flag)
{
    std::regex reg(flag.data());
    std::sregex_token_iterator iter(value.begin(), value.end(), reg, -1);
    std::sregex_token_iterator end;
 
    std::vector<std::string> vec = std::vector<std::string>(iter, end);
    return vec;
}

std::string find_password(std::string key)
{
    std::ifstream file;
    file.open("./passwords.txt");

    std::string value;
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> aux = split(line, "=");
            if (aux.at(0) == key)
            {
                value = aux.at(1);
                break;
            }
        }
    }
    file.close();
    return value;
}

bool save_password(std::string key, std::string value)
{
    std::string aux = find_password(key);
    std::ofstream file;
    file.open("./passwords.txt", std::ofstream::app);
    file << key << "=" << value << "\n";
    file.close();
    return true;
}