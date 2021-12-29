#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    int sx = data.words[0][0].size();
    int sy = data.words.size();
    long count = 0;

    bool moved;
    do
    {
        auto copy = data.words;
        moved = false;

        for(long y = 0; y < sy; y++)
        for(long x = 0; x < sx; x++)
        {
            if (data.words[y][0][x] == '>' && data.words[y][0][(x + 1) % sx] == '.')
            {
                copy[y][0][x] = '.';
                copy[y][0][(x + 1) % sx] = '>';
                moved = true;
            }
        }
        data.words = copy;
        for(long y = 0; y < sy; y++)
        for(long x = 0; x < sx; x++)
        {
            if (data.words[y][0][x] == 'v' && data.words[(y + 1) % sy][0][x] == '.')
            {
                copy[y][0][x] = '.';
                copy[(y + 1) % sy][0][x] = 'v';
                moved = true;
            }
        }
        data.words = copy;
        count++;
    }
    while(moved);
    std::cout << count << std::endl;

}
