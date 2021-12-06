#include <iostream>
#include <map>
#include <set>
#include "data.h"

using std::map, std::multimap, std::string, std::cout, std::endl, std::vector;

std::map<char, string> getReplacements()
{
    map<char, string> ret{{',', " "}};
    return ret;
}

void process(Data& data)
{
    auto draws = data.numbers[0];
    multimap<long, long> drawImpact;
    map<long, long> countsPerRowCol;
    map<long, long> boardSum;
    vector<bool> inPlay;

    for(long l = 2; l < data.numbers.size(); l+=6) // skip 6 lines to go to next board
    {
        for(long i = 0; i < 5; i++)
        for(long j = 0; j < 5; j++)
        {
            // board * 10 + id for row or column
            drawImpact.insert({data.numbers[l + i][j], (l-2)/6*10 + i});
            drawImpact.insert({data.numbers[l + i][j], (l-2)/6*10 + 5 + j});
            boardSum[(l-2)/6] += data.numbers[l + i][j];
        }
        inPlay.push_back(true);
    }

    for(long i=0; i < draws.size(); i++)
    {
        long n = draws[i];
        for(auto it = drawImpact.lower_bound(n); it != drawImpact.upper_bound(n); it++)
        {
            long board = (it->second / 10);
            countsPerRowCol[it->second]++;

            if (inPlay[board] && countsPerRowCol[it->second] == 5)
            {
                inPlay[board] = false;
                long sumSoFar = 0;

                for(long j=0; j <= i; j++)
                {
                    int n2 = draws[j];
                    for(auto it2 = drawImpact.lower_bound(n2); it2 != drawImpact.upper_bound(n2); it2++)
                    {
                        if (it2->second / 10 == board)
                        {
                            sumSoFar += n2;
                            break;
                        }
                    }
                }

                cout << (boardSum[board] - sumSoFar) * n << endl;
            }
        }
    }

}
