#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

std::map<std::pair<long, long>, long> w;
std::map<std::pair<long, long>, long> w2;
long background = 0;

long get(long y, long x)
{
    if ( w.find({y, x}) != w.end() )
    {
        return w[{y, x}];
    }
    return background;
}

void process(Data& data)
{
    std::cout << data.words[0] << std::endl;
    long x,y;

    for(y = 2; y < data.words.size(); y++)
    for(x = 0; x < data.words[y][0].size(); x++)
    {
        if (data.words[y][0][x] == '#')
        {
            w[{y - 2,x}] = 1;
        }
    }

    for(long step = 0; step < 50; step++)
    {
        long margin = 2;
        long minX = 0;
        long maxX = 0;
        long minY = 0;
        long maxY = 0;

        for(auto i:w)
        {
            minX = std::min(minX, i.first.second);
            maxX = std::max(maxX, i.first.second);
            minY = std::min(minY, i.first.first);
            maxY = std::max(maxY, i.first.first);
        }

        for(long y = minY - margin; y <= maxY + margin; y++)
        for(long x = minX - margin; x <= maxX + margin; x++)
        {
            long code =
                get(y - 1, x - 1) * 256 +
                get(y - 1, x + 0) * 128 +
                get(y - 1, x + 1) * 64 +
                get(y + 0, x - 1) * 32 +
                get(y + 0, x + 0) * 16 +
                get(y + 0, x + 1) * 8 +
                get(y + 1, x - 1) * 4 +
                get(y + 1, x + 0) * 2 +
                get(y + 1, x + 1) * 1;

            w2[{y,x}] = data.words[0][0][code] == '#';
        }

        w = std::move(w2);
        w2.clear();

        long count = 0;
        for(auto i:w)
        {
            if (i.second)
            {
                count++;
            }
        }
        std::cout << "After " << step << " steps, we have " << count << " marks" << std::endl;

        if (data.words[0][0][0] == '#')
        {
            background = 1 - background;
        }
    }
}
