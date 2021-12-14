#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{',', " "}, {'=', " "}};
    return ret;
}

void process(Data& data)
{
    long end = 0;
    bool first = true;
    std::set<std::pair<long,long>> dots;

    for(long i = 0; i < data.numbers.size(); i++)
    {
        if (end == 0 && data.words[i].size() < 1)
        {
            end = i;
        }
        if (data.words[i].size() && data.words[i][0] == "fold")
        {
            for(long j=0; j<end; j++)
            {
                long flip = data.numbers[i][3];
                if (data.words[i][2] == "x")
                {
                    if (data.numbers[j][0] > flip)
                    {
                        data.numbers[j][0] = flip - (data.numbers[j][0] - flip);
                    }
                }
                else
                {
                    if (data.numbers[j][1] > flip)
                    {
                        data.numbers[j][1] = flip - (data.numbers[j][1] - flip);
                    }
                }
            }

            dots.clear();
            for(long j=0; j<end; j++)
            {
                dots.insert({data.numbers[j][0], data.numbers[j][1]});
            }

            if (first)
            {
                std::cout << dots.size() << std::endl;
                first = false;
            }
        }
    }

    std::vector<std::string> out;
    for(auto p:dots)
    {
        if (p.second >= out.size())
        {
            out.resize(p.second + 1);
        }
        if (p.first >= out[p.second].size())
        {
            out[p.second].resize(p.first + 1, ' ');
        }
        out[p.second][p.first] = '*';
    }

    for(auto s:out)
    {
        std::cout << s << std::endl;
    }
}
