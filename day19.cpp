#include <iostream>
#include "data.h"

using std::cout, std::endl;

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

std::vector<std::vector<Point>> BeaconsByScanner;
std::vector<bool> matched;

std::vector<Point> beacons;

bool align(long i, long j)
{
    long xGoesTo;
    long yGoesTo;
    long zGoesTo;
    long xSign;
    long ySign;
    long zSign;

    std::set<Point> is;

    for(long i0 = 0; i0 < BeaconsByScanner[i].size(); i0++)
    {
        is.insert(BeaconsByScanner[i][i0]);
    }

    for(long orient = 0; orient < 3 * 2 * 8; orient++)
    {
        xGoesTo = orient % 3;
        yGoesTo = ((orient / 3) % 2 + xGoesTo + 1) % 3;
        zGoesTo = 3 ^ xGoesTo ^ yGoesTo;
        xSign = (orient / 6) % 2 ? 1 : -1;
        ySign = (orient / 12) % 2 ? 1 : -1;
        zSign = (orient / 24) % 2 ? 1 : -1;


        for(long i0 = 0; i0 < BeaconsByScanner[i].size(); i0++)
        for(long j0 = 0; j0 < BeaconsByScanner[j].size(); j0++)
        {
            long count = 0;
            for(long jIt = 0; jIt < BeaconsByScanner[j].size(); jIt++)
            {
                if (jIt != j0)
                {
                    long p[3];
                    p[0] = (BeaconsByScanner[j][jIt].v[0] - BeaconsByScanner[j][j0].v[0]) * xSign;
                    p[1] = (BeaconsByScanner[j][jIt].v[1] - BeaconsByScanner[j][j0].v[1]) * ySign;
                    p[2] = (BeaconsByScanner[j][jIt].v[2] - BeaconsByScanner[j][j0].v[2]) * zSign;

                    Point toFind = BeaconsByScanner[i][i0];
                    toFind.v[0] += p[xGoesTo];
                    toFind.v[1] += p[yGoesTo];
                    toFind.v[2] += p[zGoesTo];

                    if (is.find(toFind) != is.end())
                    {
                        count++;
                    }
                }
            }

            if (count >= 11)
            {
                for(long jIt = 0; jIt < BeaconsByScanner[j].size(); jIt++)
                {
                    long p[3];
                    p[0] = (BeaconsByScanner[j][jIt].v[0] - BeaconsByScanner[j][j0].v[0]) * xSign;
                    p[1] = (BeaconsByScanner[j][jIt].v[1] - BeaconsByScanner[j][j0].v[1]) * ySign;
                    p[2] = (BeaconsByScanner[j][jIt].v[2] - BeaconsByScanner[j][j0].v[2]) * zSign;

                    Point found = BeaconsByScanner[i][i0];
                    found.v[0] += p[xGoesTo];
                    found.v[1] += p[yGoesTo];
                    found.v[2] += p[zGoesTo];

                    BeaconsByScanner[i].push_back(found); // replace beacons in j in coord system of i
                }

                long z[3];
                z[0] = -BeaconsByScanner[j][j0].v[0] * xSign;
                z[1] = -BeaconsByScanner[j][j0].v[1] * ySign;
                z[2] = -BeaconsByScanner[j][j0].v[2] * zSign;
                Point zero = BeaconsByScanner[i][i0];
                zero.v[0] += z[xGoesTo];
                zero.v[1] += z[yGoesTo];
                zero.v[2] += z[zGoesTo];

                // assumes matches are always 0-something (which empirically holds)
                beacons.push_back(zero);

                BeaconsByScanner[j].clear();
                matched[j] = true;

                std::cout << "matches " << i << " and " << j << std::endl;
                return true;
            }
        }
    }

    return false;
}

void process(Data& data)
{
    long scanner = -1;
    for(long i = 0; i < data.words.size(); i++)
    {
        if (data.words[i].size() > 1 && data.words[i][1] == "scanner")
        {
            scanner++;
            BeaconsByScanner.push_back({});
        }
        if (data.numbers[i].size() == 3)
        {
            BeaconsByScanner[scanner].push_back({data.numbers[i][0], data.numbers[i][1], data.numbers[i][2]});
        }
    }

    matched.resize(BeaconsByScanner.size());
    matched[0] = true;

    bool match = false;

    do
    {
        match = false;
        for(long i = 0; i < matched.size(); i++)
        {
            if (matched[i])
            {
                for(long j = 0; j < matched.size(); j++)
                {
                    if (!matched[j])
                    {
                        if (align(i, j))
                        {
                            match = true;
                        }
                    }
                }
            }
        }
    }
    while(match);

    for(long i = 0; i < matched.size(); i++)
    {
        std::set<Point> is;

        for(long i0 = 0; i0 < BeaconsByScanner[i].size(); i0++)
        {
            is.insert(BeaconsByScanner[i][i0]);
        }
        if (is.size())
        {
            cout << is.size() << endl;
        }
    }

    long bestD = 0;
    for(auto b:beacons)
    for(auto c:beacons)
    {
        long d =
            std::abs(b.v[0] - c.v[0]) +
            std::abs(b.v[1] - c.v[1]) +
            std::abs(b.v[2] - c.v[2]);

        bestD = std::max(bestD, d);
    }
    std::cout << bestD << endl;
}
