#include <iostream>
#include <queue>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

int paint(Data& data, int x, int y, int sx, int sy)
{
    std::deque<int> pos;
    pos.push_back(x);
    pos.push_back(y);
    int count = 0;

    bool added = false;
    do
    {
        x = pos.front(); pos.pop_front();
        y = pos.front(); pos.pop_front();

        if (data.words[y][0][x] != '9')
        {
            if ((y > 0) && ('9' != data.words[y - 1][0][x]))
            {
                pos.push_back(x);
                pos.push_back(y - 1);
            }
            if ((x > 0) && ('9' != data.words[y][0][x - 1]))
            {
                pos.push_back(x - 1);
                pos.push_back(y);
            }
            if ((y < sy - 1) && ('9' != data.words[y + 1][0][x]))
            {
                pos.push_back(x);
                pos.push_back(y + 1);
            }
            if ((x < sx - 1) && ('9' != data.words[y][0][x + 1]))
            {
                pos.push_back(x + 1);
                pos.push_back(y);
            }
            data.words[y][0][x] = '9';
            count++;
        }
    }
    while(!pos.empty());

    return count;
}

void process(Data& data)
{
    int sx = data.words[0][0].size();
    int sy = data.words.size();
    int count = 0;
    std::vector<int> starts;

    for(int y = 0; y < sy; y++)
    {
        for(int x = 0; x < sx; x++)
        {
            if ((y > 0 && data.words[y][0][x] >= data.words[y - 1][0][x]) ||
                (x > 0 && data.words[y][0][x] >= data.words[y][0][x - 1]) ||
                (y < sy - 1 && data.words[y][0][x] >= data.words[y + 1][0][x]) ||
                (x < sx - 1 && data.words[y][0][x] >= data.words[y][0][x + 1]))
                {
                    continue;
                }
            count += 1 + (data.words[y][0][x] - '0');
            starts.push_back(x);
            starts.push_back(y);
        }
    }
    std::cout << count << std::endl;
    std::vector<int> sizes;

    for(int i=0; i < starts.size(); i += 2)
    {
        sizes.push_back(paint(data, starts[i], starts[i + 1], sx, sy));
    }
    std::sort(sizes.begin(), sizes.end());
    std::cout << sizes[sizes.size() - 1] * sizes[sizes.size() - 2] * sizes[sizes.size() - 3] << std::endl;
}
