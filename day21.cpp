#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process0(Data& data)
{
    long p[2];
    long next = 0;
    long s[2];
    long die = 1;

    s[0] = 0;
    s[1] = 0;

    p[0] = data.numbers[0][4];
    p[1] = data.numbers[1][4];

    do
    {
        p[next] += die;
        die++;
        p[next] += die;
        die++;
        p[next] += die;
        die++;

        p[next] = ((p[next] - 1) % 10) + 1;

        s[next] += p[next];
        next = 1 - next;
    }
    while(s[0] < 1000 && s[1] < 1000);

    std::cout << s[next] * (die - 1) << std::endl;
}

void process1(Data& data)
{
    long target = 21;
    long values[27] = {
        1+1+1,
        1+1+2,
        1+1+3,
        1+2+1,
        1+2+2,
        1+2+3,
        1+3+1,
        1+3+2,
        1+3+3,
        2+1+1,
        2+1+2,
        2+1+3,
        2+2+1,
        2+2+2,
        2+2+3,
        2+3+1,
        2+3+2,
        2+3+3,
        3+1+1,
        3+1+2,
        3+1+3,
        3+2+1,
        3+2+2,
        3+2+3,
        3+3+1,
        3+3+2,
        3+3+3};

    std::map<std::vector<long>, long> countsByScorePosNext;
    std::map<std::vector<long>, long> nextCountsByScorePosNext;

    countsByScorePosNext[{0,0,data.numbers[0][4],data.numbers[1][4],0}] = 1;
    long counts[2] = {0,0};

    bool again;
    do
    {
        again = false;
        nextCountsByScorePosNext.clear();

        for(auto it:countsByScorePosNext)
        {
            for(long die = 0; die < 27; die++)
            {
                auto state = it.first;

                // update position
                state[state[4] + 2] += values[die];
                state[state[4] + 2] = (state[state[4] + 2] - 1) % 10 + 1;

                // update score
                state[state[4] + 0] += state[state[4] + 2];
                state[4] = 1 - state[4];

                if (state[0] < target && state[1] < target)
                {
                    nextCountsByScorePosNext[state] += it.second;
                    again = true;
                }
                else if (state[0] >= target)
                {
                    counts[0] += it.second;
                }
                else
                {
                    counts[1] += it.second;
                }
            }
        }
        countsByScorePosNext = nextCountsByScorePosNext;
    }
    while(again);
    std::cout << std::max(counts[0], counts[1]) << std::endl;
}


void process(Data& data)
{
    process0(data);
    process1(data);


}
