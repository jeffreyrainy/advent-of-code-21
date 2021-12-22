#include <iostream>
#include "data.h"

// terribly inefficient one!!
// use an octree next time.

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'=', " "}, {'.', " "}, {',', " "}, {'x', ""}, {'y', ""}, {'z', ""} };
    return ret;
}

class Point
{
public:
    long v[3];
    bool operator<(const Point& that) const
    {
        return ((v[0] < that.v[0]) ||
                (v[0] == that.v[0] && v[1] < that.v[1]) ||
                (v[0] == that.v[0] && v[1] == that.v[1] && v[2] < that.v[2]));
    }
};

long limit = 50;

void squishAxis(std::map<long, long>& xmap, std::map<long, long>& xweight, const std::set<long>& xs)
{
    bool first = true;
    long prev;
    long used;

    for(auto i:xs)
    {
        if (!first)
        {
            long weight = i - prev - 1;

            if (weight)
            {
                xweight[used + 1] = weight;
                xweight[used + 2] = 1;
                xmap[i] = used + 2;
                used += 2;
            }
            else
            {
                xweight[used + 1] = 1;
                xmap[i] = used + 1;
                used += 1;
            }

            prev = i;
        }
        else
        {
            xmap[i] = 0;
            xweight[xmap[i]] = 1;
            prev = i;
            used = 0;
        }

        first = false;
    }

}


void count(Data& data)
{
    std::map<Point, long> points;
    std::set<long> xs;
    std::set<long> ys;
    std::set<long> zs;

    // find the used x,y,z values
    for(long i = 0; i < data.words.size(); i++)
    {
        xs.insert(data.numbers[i][1]);
        xs.insert(data.numbers[i][2]);
        ys.insert(data.numbers[i][3]);
        ys.insert(data.numbers[i][4]);
        zs.insert(data.numbers[i][5]);
        zs.insert(data.numbers[i][6]);
    }

    xs.insert(-limit);
    xs.insert(limit);
    ys.insert(-limit);
    ys.insert(limit);
    zs.insert(-limit);
    zs.insert(limit);

    std::map<long, long> xmap;
    std::map<long, long> xweight;
    std::map<long, long> ymap;
    std::map<long, long> yweight;
    std::map<long, long> zmap;
    std::map<long, long> zweight;

    squishAxis(xmap, xweight, xs);
    squishAxis(ymap, yweight, ys);
    squishAxis(zmap, zweight, zs);

    for(long i = 0; i < data.words.size(); i++)
    {
        long x0 = data.numbers[i][1] < -limit ? xmap[-limit] : xmap[data.numbers[i][1]];
        long y0 = data.numbers[i][3] < -limit ? ymap[-limit] : ymap[data.numbers[i][3]];
        long z0 = data.numbers[i][5] < -limit ? zmap[-limit] : zmap[data.numbers[i][5]];
        long x1 = data.numbers[i][2] > limit ? xmap[limit] : xmap[data.numbers[i][2]];
        long y1 = data.numbers[i][4] > limit ? ymap[limit] : ymap[data.numbers[i][4]];
        long z1 = data.numbers[i][6] > limit ? zmap[limit] : zmap[data.numbers[i][6]];

        long value = data.words[i][0] == "on";

        for(long x = x0; x <= x1; x++)
        for(long y = y0; y <= y1; y++)
        for(long z = z0; z <= z1; z++)
        {
            points[{x,y,z}] = value;
        }

        std::cout << i << "/" << data.words.size() << std::endl;
    }

    long count = 0;
    long progress = 0;
    for(auto& p:points)
    {
        progress++;
        if (p.second)
        {
            count += xweight[p.first.v[0]] * yweight[p.first.v[1]] * zweight[p.first.v[2]];
        }

        if (progress % 10000 == 0)
        {
            std::cout << progress * 100 / points.size() << std::endl;
        }
    }
    std::cout << count << std::endl;
}

void process(Data& data)
{
    limit = 50;
    count(data);

    limit = 1000000;
    count(data);
}
