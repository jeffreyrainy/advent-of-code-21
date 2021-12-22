#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}};
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

std::vector<std::vector<Point>> beaconsByPoints;
std::vector<bool> matched;

long align(long i, long j)
{
    long xGoesTo;
    long yGoesTo;
    long zGoesTo;
    long xSign;
    long ySign;
    long zSign;

    std::set<Point> is;

    for(long i0 = 0; i0 < beaconsByPoints[i].size(); i0++)
    {
        is.insert(beaconsByPoints[i][i0]);
    }

    for(long orient = 0; orient < 3 * 2 * 8; orient++)
    {
        xGoesTo = orient % 3;
        yGoesTo = ((orient / 3) % 2 + xGoesTo + 1) % 3;
        zGoesTo = 3 ^ xGoesTo ^ yGoesTo;
        xSign = (orient / 6) % 2 ? 1 : -1;
        ySign = (orient / 12) % 2 ? 1 : -1;
        zSign = (orient / 24) % 2 ? 1 : -1;


        for(long i0 = 0; i0 < beaconsByPoints[i].size(); i0++)
        for(long j0 = 0; j0 < beaconsByPoints[j].size(); j0++)
        {


        }
    }

    return 0;
}

void process(Data& data)
{
    long scanner = -1;
    for(long i = 0; i < data.words.size(); i++)
    {
        if (data.words[i].size() > 1 && data.words[i][1] == "scanner")
        {
            scanner++;
            beaconsByPoints.push_back({});
        }
        if (data.numbers[i].size() == 3)
        {
            beaconsByPoints[scanner].push_back({data.numbers[i][0], data.numbers[i][1], data.numbers[i][2]});
        }
    }

    matched.resize(beaconsByPoints.size());
    matched[0] = true;

    bool match = false;


    do
    {
        long bestScore = 0;
        match = false;
        for(long i = 0; i < matched.size(); i++)
        {
            if (!matched[i])
            {
                for(long j = 0; j < matched.size(); j++)
                {
                    if (matched[j])
                    {
                        long score = align(i, j);
                        if (score > bestScore)
                        {
                            bestScore = score;
                        }
                    }
                }
            }
        }




    }
    while(match);




}
