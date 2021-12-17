#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'-', " "}, {'>', " "}};
    return ret;
}

std::map<std::string, std::string> rep;

void process2(Data& data);
void process(Data& data)
{

    auto copy = data.words;

    std::string curr = copy[0][0];

    for(long i = 2; i < copy.size(); i++)
    {
        std::string one;
        one = copy[i][1];

        copy[i][1].resize(1);
        copy[i][1][1] = copy[i][1][0] - 'A' + 'a';

        rep[copy[i][0]] = copy[i][1];
    }

    for(long step = 0; step < 10; step++)
    {
        std::string out;
        char prev = curr[0];

        for(int i = 1; i < curr.length(); i++)
        {
            std::string search = "  ";
            search[0] = prev;
            search[1] = curr[i];
            prev = search[1];

            out += curr[i-1];
            if (rep.find(search) != rep.end())
            {
                out += rep[search];
            }
        }

        curr = out + prev;

        for(char& c: curr)
        {
            c = toupper(c);
        }
    }

    std::map<char, long> counts;
    for(char& c: curr)
    {
        counts[c]++;
    }
    bool first = true;
    long min=0, max=0;
    for(auto i:counts)
    {
        if (first || i.second > max)
        {
            max = i.second;
        }
        if (first || i.second < min)
        {
            min = i.second;
        }
        first = false;
    }

    std::cout << max << " " << min << " " << max-min << std::endl;

    process2(data);
}

void process2(Data& data)
{
    std::map<std::string, long> counts;
    std::map<std::string, long> counts2;
    std::string curr = data.words[0][0];

    for(long i=0; i<curr.length()-1; i++)
    {
        counts[curr.substr(i,2)]++;
    }

    for(long step=0; step<40; step++)
    {

        for(auto i: counts)
        {
            std::string tok = "  ";
            tok[0] = i.first[0];
            tok[1] = rep[i.first][0];

            counts2[tok] += i.second;

            tok[0] = rep[i.first][0];
            tok[1] = i.first[1];

            counts2[tok] += i.second;
        }
        counts = counts2;
        counts2.clear();
    }

    std::map<char, long> letters;

    for(auto i: counts)
    {
        letters[i.first[0]] += i.second;
    }
    letters[data.words[0][0][data.words[0][0].size() - 1]]++;

    bool first = true;
    long min=0, max=0;
    for(auto i:letters)
    {
        if (first || i.second > max)
        {
            max = i.second;
        }
        if (first || i.second < min)
        {
            min = i.second;
        }
        first = false;
    }

    std::cout << max << " " << min << " " << max-min << std::endl;

}