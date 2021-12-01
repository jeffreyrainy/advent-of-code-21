#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include "data.h"

int main()
{
    std::string line;
    std::string line2;
    Data d;

    while(std::getline(std::cin, line))
    {
        line2 = "";
        auto rep = getReplacements();

        for(auto c: line)
        {
            if (rep.find(c) != rep.end())
            {
                line2 += rep[c];
            }
            else
            {
                line2 += c;
            }
        }

        std::istringstream iss{line2};

        std::string word;

        d.words.resize(d.words.size() + 1);
        d.numbers.resize(d.numbers.size() + 1);

        while(iss >> word)
        {
            d.words[d.words.size() - 1].push_back(word);
            d.numbers[d.numbers.size() - 1].push_back(std::atoi(word.c_str()));

        }
        d.raw.push_back(line2);
    }

    process(d);

    return 0;
}