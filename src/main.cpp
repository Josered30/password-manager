#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include "generator.hpp"
#include "manager.hpp"
#include "encryption.hpp"

std::pair<std::string, std::string> tokenizer(char *value, char *delim)
{
    std::pair<std::string, std::string> pair = std::pair<std::string, std::string>();

    char *token = strtok(value, delim);
    pair.first = token;

    token = strtok(NULL, delim);
    pair.second = token;

    return pair;
}

std::vector<std::pair<std::string, std::string>> parse_args(int argsc, char *argv[])
{
    std::vector<std::pair<std::string, std::string>> vect = std::vector<std::pair<std::string, std::string>>();
    vect.reserve(argsc);

    for (int i = 1; i < argsc; ++i)
    {
        std::string key;
        std::string value;
        std::string arg = std::string(argv[i]);
        std::pair<std::string, std::string> pair = std::pair<std::string, std::string>();

        if (arg.find("=") != std::string::npos)
        {
            pair = tokenizer(argv[i], (char *)"=");
            vect.push_back(pair);
        }
        else
        {
            pair.first = arg;
            vect.push_back(pair);
        }
    }
    return vect;
}

bool exist(std::string name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argsc, char *argv[])
{
    if (argsc == 1)
    {
        std::cout << "none" << std::endl;
        return 0;
    }

    int lenght = 10;
    bool number = true;
    bool special = true;
    std::string name;
    std::string aes_key;

    bool io = true;

    std::vector<std::pair<std::string, std::string>> args = parse_args(argsc, argv);

    std::for_each(args.begin(), args.end(), [&](std::pair<std::string, std::string> e)
                  {
                      std::string key = e.first;
                      std::string value = e.second;

                      if (key == "-n")
                      {
                          number = value == "true" ? true : false;
                      }

                      if (key == "-s")
                      {
                          special = value == "true" ? true : false;
                      }

                      if (key == "-l")
                      {
                          lenght = std::stoi(value);
                      }

                      if (key == "-n")
                      {
                          name = value;
                      }

                      if (key == "-i")
                      {
                          io = true;
                      }

                      if (key == "-o")
                      {
                          io = false;
                      }

                      if (key == "-k")
                      {
                          aes_key = value;
                      }
                  });

    if (!aes_key.empty())
    {

        if (io)
        {

            if (exist(".\\passwords.txt") && !find_password(name).empty())
            {
                std::cout << "Password already exist" << std::endl;
                return 0;
            }

            std::string result = get_password(lenght, number, special);
            std::cout << result << std::endl;
            std::string encrypted = encrypt(result, aes_key);
            save_password(name, to_hex(encrypted));
        }
        else
        {
            if (exist(".\\passwords.txt"))
            {
                std::string find = find_password(name);
                std::string decrypted = decrypt(from_hex(find), aes_key);
                std::cout << decrypted << std::endl;
            }
            else
            {
                std::cout << "Password file don't exist" << std::endl;
            }
        }
    }

    return 0;
}