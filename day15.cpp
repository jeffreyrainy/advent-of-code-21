#include <iostream>
#include <queue>

#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

typedef std::pair<int,int> Point;

class Compare
{
public:
    bool operator()(std::pair<int, Point> a, std::pair<int, Point> b)
    {
        return a.first > b.first;
    }
};

int sx, sy;
std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, Compare> todo;
std::map<Point, int> totalRisk;
Data* data;

void go(std::pair<int, Point> top, int dy, int dx)
{
    auto from = top.second;

    if ((from.first + dy >= 0) && (from.first + dy < sy) && (from.second + dx >= 0) && (from.second + dx < sx) &&
        (totalRisk[{from.first + dy, from.second + dx}] == 0))
    {
        totalRisk[{from.first + dy, from.second + dx}] = top.first + (data->words[from.first + dy][0][from.second + dx] - '0');
        todo.push({totalRisk[{from.first + dy, from.second + dx}], {from.first + dy, from.second + dx}});
    }
}

void grow(Data& data0)
{
    auto copy = data0;

    sy = data0.words.size();
    sx = data0.words[0][0].size();

    for(int x = 1; x < 5; x++)
    {
        for(int y = 0; y < sy; y++)
        {
            copy.words[y][0] += data0.words[y][0];
            for(int i = 0; i < sx; i++)
            {
                copy.words[y][0][sx * x + i] += x;
                if (copy.words[y][0][sx * x + i] > '9')
                {
                    copy.words[y][0][sx * x + i] -= 9;
                }
            }
        }
    }

    for(int y = 1; y < 5; y++)
    {
        for(int yi = 0; yi < sy; yi++)
        {
            copy.words.push_back(copy.words[yi]);
            for(auto& c: copy.words[copy.words.size() - 1][0])
            {
                c += y;
                if (c > '9') c -= 9;
            }
        }
    }

    data[0] = copy;

}


void process(Data& data0)
{
    data = &data0;

    grow(data0);

    totalRisk[{0,0}] = 0;
    todo.push({0, {0,0}});

    sy = data->words.size();
    sx = data->words[0][0].size();

    while (!todo.empty())
    {
        std::pair<int, Point> top = todo.top();
        todo.pop();

        go(top, -1, 0);
        go(top, 1, 0);
        go(top, 0, -1);
        go(top, 0, 1);
    }

    std::cout << totalRisk[{sy / 5 - 1, sx / 5 - 1}] << std::endl;
    std::cout << totalRisk[{sy - 1, sx - 1}] << std::endl;
}
