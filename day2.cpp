#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    int x = 0;
    int y = 0;

    int y2 = 0;
    int aim = 0;
    for(int i=0; i < data.numbers.size(); i++)
    {
        if (data.words[i][0] == "forward")
        {
            x += data.numbers[i][1];
            y2 += aim * data.numbers[i][1];
        }
        if (data.words[i][0] == "up")
        {
            y -= data.numbers[i][1];
            aim -= data.numbers[i][1];
        }
        if (data.words[i][0] == "down")
        {
            y += data.numbers[i][1];
            aim += data.numbers[i][1];
        }
    }

    std::cout << x * y << std::endl;
    std::cout << x * y2 << std::endl;
}
