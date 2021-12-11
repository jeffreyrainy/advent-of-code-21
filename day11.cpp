#include <iostream>
#include <queue>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

int sx, sy;

void draw(std::vector<std::vector<std::string>> level)
{
    for(int y = 0; y < sy; y++)
    {
        std::cout << level[y][0] << std::endl;
    }
    std::cout << std::endl;

}

void process(Data& data)
{
    sx = data.words[0][0].size();
    sy = data.words.size();
    long count = 0;
    std::vector<int> starts;

    bool again = false;
    bool part1 = false, part2 = false;
    long flashed = 0;

    auto level = data.words;

    char ten = '9' + 1;
    char done = '9' + 2;

    int step = 0;
    while(!part1 || !part2)
    {
        for(int y = 0; y < sy; y++)
        {
            for(int x = 0; x < sx; x++)
            {
                if (level[y][0][x] != ten) level[y][0][x]++;
            }
        }

        do
        {
            again = false;
            for(int y = 0; y < sy; y++)
            {
                for(int x = 0; x < sx; x++)
                {
                    if (level[y][0][x] == ten)
                    {
                        for(int i = -1; i < 2; i++)
                        for(int j = -1; j < 2; j++)
                        if ((y+i) >= 0 && (x+j) >= 0 && (i || j) &&
                            (y+i) < sy && (x+j) < sx)
                        {
                            if (level[y+i][0][x+j] != ten && level[y+i][0][x+j] != done)
                            {
                                level[y+i][0][x+j]++;
                                again = true;
                            }
                        }
                        level[y][0][x] = done;
                        flashed++;
                    }
                }
            }
        }
        while(again);

        long flashedNow = 0;
        for(int y = 0; y < sy; y++)
        {
            for(int x = 0; x < sx; x++)
            {
                if (level[y][0][x] == done)
                {
                    level[y][0][x] = '0';
                    flashedNow++;
                }
            }
        }

        step++;

        if (flashedNow == sx * sy)
        {
            std::cout << "Part 2: " << step  << std::endl;
            part2 = true;
        }

        if (step == 100)
        {
            std::cout << "Part 1: " << flashed << std::endl;
            part1 = true;
        }
    }
}
