#include <iostream>
#include "data.h"

using namespace std;

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

bool check(const vector<int64_t>& row)
{
    int bad = 0;
    for(int j = 0; j < row.size() - 1; j++)
    {
        if ((row[j] <= row[j+1]) ||
            (row[j] - row[j + 1] > 3))
        {
            bad++;
            break;
        }
    }
    for(int j = 0; j < row.size() - 1; j++)
    {
        if ((row[j] >= row[j+1]) ||
            (row[j] - row[j + 1] < -3))
        {
            bad++;
            break;
        }
    }
    return bad < 2;
}

void process(Data& data)
{
    int count = 0;
    int count2 = 0;
    for(int i = 0; i < data.numbers.size(); i++)
    {
        if (check(data.numbers[i]))
        {
            count++;
        }
        for(int j = 0; j < data.numbers[i].size(); j++)
        {
            auto r = data.numbers[i];
            r.erase(r.begin() +  j);
            if (check(r))
            {
                count2++;
                break;
            }
        }
    }

    cout << count << endl;
    cout << count2 << endl;
}
