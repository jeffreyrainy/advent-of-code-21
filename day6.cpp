#include <iostream>
#include "data.h"


std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',',  " "}};
    return ret;
}

void process(Data& data)
{
    std::map<long, long> counts;
    std::map<long, long> counts2;

    for(auto x: data.numbers[0])
    {
        counts[x]++;
    }

    for(int d = 0; d < 256; d++)
    {
        counts2.clear();
        for(auto i: counts)
        {
            if (i.first == 0)
            {
                counts2[6] += i.second;
                counts2[8] += i.second;
            }
            else
            {
                counts2[i.first - 1] += i.second;
            }
        }
        counts = counts2;

        if (d + 1 == 80 || d + 1 == 256)
        {
            long sum = 0;
            for(auto i: counts)
            {
                sum += i.second;
            }
            std::cout << sum << std::endl;
        }
    }
}
