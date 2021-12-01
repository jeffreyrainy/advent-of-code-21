#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    int count = 0;
    for(int i = 1; i < data.numbers.size(); i++)
    {
        if (data.numbers[i][0] > data.numbers[i - 1][0])
        {
            count ++;
        }
    }
    std::cout << count << std::endl;

    count = 0;
    for(int i = 3; i < data.numbers.size(); i++)
    {
        if (data.numbers[i][0] > data.numbers[i - 3][0])
        {
            count ++;
        }
    }
    std::cout << count << std::endl;
}
