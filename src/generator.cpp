#include <string>
#include <random>
#include <time.h>
#include <algorithm>

std::string get_password(int length, bool numbers, bool special)
{
    std::string chars[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ","1234567890","!@#$%^&*()`~-_+[{]{|;:'\",<.>/?"};
    std::random_device rd;
    std::mt19937 generator(rd());

    int flag = 0;
    if (numbers)
        ++flag;
    if (special)
        ++flag;

    std::uniform_int_distribution<> distrib(0, flag);

    std::string output;
    output.reserve(length);

    while (length > 0)
    {
        auto rand_number = generator();
        while (rand_number > 100)
        {
            int r = distrib(generator);
            int r_length = chars[r].length();
            output.push_back(chars[r][rand_number % r_length]);
            rand_number /= r_length;
            --length;
        }
    }
    return output;
}