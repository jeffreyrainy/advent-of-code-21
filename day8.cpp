#include <iostream>
#include <set>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

std::string match(std::string a, std::string b)
{
    std::string ret;
    for(auto c: a)
    {
        if (b.find(c) == std::string::npos)
        {
            ret += c;
        }
    }
    for(auto c: b)
    {
        if (a.find(c) == std::string::npos)
        {
            ret += c;
        }
    }

    return ret;
}

void adjust(int unknown, int known, int count, std::map<int, std::set<std::string>>& poss)
{
    for(auto p2:poss[unknown])
    {
        if (match(p2, *poss[known].begin()).length() == count)
        {
            poss[unknown] = {p2};
            for(auto& i:poss)
            {
                if (i.first != unknown)
                {
                    i.second.erase(p2);
                }
            }
            break;
        }
    }
}

void process(Data& data)
{
    int count = 0;
    int total = 0;

    std::map<int, std::set<int>> counts = {
        {2,{1}},
        {3,{7}},
        {4,{4}},
        {5,{2,3,5}},
        {6,{0,6,9}},
        {7,{8}} };

    for(auto lines:data.words)
    {
        std::map<std::string, int> mapping;
        std::map<int, std::set<std::string>> poss;

        bool after = false;
        for(auto word: lines)
        {
            auto sword = word;
            std::sort(sword.begin(), sword.end());

            if (word == "|")
            {
                after = true;
            }
            if (after)
            {
                if (word.length() == 2)
                {
                    count++;
                }
                if (word.length() == 4)
                {
                    count++;
                }
                if (word.length() == 3)
                {
                    count++;
                }
                if (word.length() == 7)
                {
                    count++;
                }
            }
            for(auto i:counts[word.length()])
            {
                poss[i].insert(sword);
            }
        }

        adjust(3, 7, 2, poss); // 3 and 7 differ in 2 bars
        adjust(5, 4, 3, poss); // 5 and 4 differ in 4 bars
        adjust(6, 1, 6, poss); // 6 and 1 differ in 6 bars
        adjust(9, 4, 2, poss); // 9 and 4 differ in 2 bars

        for(auto p: poss)
        {
            assert(p.second.size() == 1);
            mapping[*p.second.begin()] = p.first;
        }

        int value = 0;
        after = false;
        for(auto word: lines)
        {
            auto sword = word;
            std::sort(sword.begin(), sword.end());

            if (sword == "|")
            {
                after = true;
            }
            else
            {
                if (after)
                {
                    value = value * 10 + mapping[sword];
                }
            }
        }
        total += value;
    }

    std::cout << count << std::endl;
    std::cout << total << std::endl;

}
