#include <iostream>
#include "data.h"

using std::map, std::cout, std::endl, std::tuple;

std::map<char, std::string> getReplacements()
{
    map<char, std::string> ret{{','," "}, {'-',""}, {'>',""}};
    return ret;
}

void process(Data& data)
{
    map<tuple<long, long>, long> counts;
    auto total = 0;

    for(auto i = 0; i < data.numbers.size(); i++)
    {
        auto dx = data.numbers[i][0] - data.numbers[i][2];
        auto dy = data.numbers[i][1] - data.numbers[i][3];

        if (dx == 0)
        {
            auto sy = data.numbers[i][1] < data.numbers[i][3] ? 1 : -1;
            auto x = data.numbers[i][0];
            for(auto y = data.numbers[i][1]; y != data.numbers[i][3] + sy; y += sy)
            {
                counts[{x,y}]++;
            }
        }
        else if (dy == 0)
        {
            auto sx = data.numbers[i][0] < data.numbers[i][2] ? 1 : -1;
            auto y = data.numbers[i][1];
            for(auto x = data.numbers[i][0]; x != data.numbers[i][2] + sx; x += sx)
            {
                counts[{x,y}]++;
            }
        }
        else
        {
            auto sx = data.numbers[i][0] < data.numbers[i][2] ? 1 : -1;
            auto sy = data.numbers[i][1] < data.numbers[i][3] ? 1 : -1;
            auto y = data.numbers[i][1];
            for(auto x = data.numbers[i][0]; x != data.numbers[i][2] + sx; x += sx)
            {
                counts[{x,y}]++;
                y += sy;
            }
        }
    }

    for(auto i:counts)
    {
        if (i.second > 1)
        {
            total++;
        }
    }

    cout << total << endl;
}
