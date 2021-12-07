#include <iostream>
#include <algorithm>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{','," "}};
    return ret;
}

void process(Data& data)
{
    std::sort(data.numbers[0].begin(), data.numbers[0].end());
    int best = 0;
    int bestI = 0;
    int best2 = 0;
    int bestI2 = 0;
    for(int i = data.numbers[0][0]; i <= data.numbers[0][data.numbers[0].size() - 1]; i++)
    {
        int sum = 0;
        int sum2 = 0;
        for(int j = 0; j < data.numbers[0].size(); j++)
        {
            int d = abs(i - data.numbers[0][j]);
            sum += d;
            sum2 += d * ( d + 1) / 2;
        }

        if (i == 0 || sum < best)
        {
            best = sum;
            bestI = i;
        }

        if (i == 0 || sum2 < best2)
        {
            best2 = sum2;
            bestI2 = i;
        }

    }

    std::cout << bestI << " " << best << std::endl;
    std::cout << bestI2 << " " << best2 << std::endl;

}
