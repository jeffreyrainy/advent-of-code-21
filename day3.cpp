#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    int epsilon = 0;
    int gamma = 0;

    for(int j=0; j < data.words[0][0].size(); j++)
    {
        int count = 0;
        for(int i=0; i < data.words.size(); i++)
        {
            if (data.words[i][0][j] == '1')
            {
                count++;
            }
            else
            {
                count--;
            }
        }

        gamma = gamma * 2 + (count >= 0);
        epsilon = epsilon * 2 + (count < 0);
    }
    std::cout << gamma * epsilon <<  std::endl;

    epsilon = 0;
    gamma = 0;

    auto copy = data.words;

    for(int j=0; j < copy[0][0].size(); j++)
    {
        int count = 0;
        for(int i=0; i < copy.size(); i++)
        {
            if (copy[i][0][j] == '1')
            {
                count++;
            }
            else
            {
                count--;
            }
        }

        for(int i=0; i < copy.size();)
        {
            if (copy.size() > 1 && ((copy[i][0][j] == '1') != (count >= 0)))
            {
                copy[i][0] = copy[copy.size() - 1][0];
                copy.resize(copy.size() - 1);
            }
            else
            {
                i++;
            }
        }
    }

    for(int j=0; j < copy[0][0].size(); j++)
    {
        gamma = gamma * 2 + (copy[0][0][j] == '1');
    }

    copy = data.words;
    for(int j=0; j < copy[0][0].size(); j++)
    {
        int count = 0;
        for(int i=0; i < copy.size(); i++)
        {
            if (copy[i][0][j] == '1')
            {
                count++;
            }
            else
            {
                count--;
            }
        }

        for(int i=0; i < copy.size();)
        {
            if (copy.size() > 1 && ((copy[i][0][j] == '1') != (count < 0)))
            {
                copy[i][0] = copy[copy.size() - 1][0];
                copy.resize(copy.size() - 1);
            }
            else
            {
                i++;
            }
        }
    }

    for(int j=0; j < copy[0][0].size(); j++)
    {
        epsilon = epsilon * 2 + (copy[0][0][j] == '1');
    }

    std::cout << gamma * epsilon <<  std::endl;


}
