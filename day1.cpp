#include <iostream>
#include "data.h"

using namespace std;

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

void process(Data& data)
{
    vector<int> l1, l2;
    map<int, int> counts1, counts2;

    for(int i = 0; i < data.numbers.size(); i++)
    {
        int i1 = data.numbers[i][0];
        int i2 = data.numbers[i][1];

        l1.push_back(i1);
        l2.push_back(i2);

        counts1[i1]++;
        counts2[i2]++;
    }

    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());
    int sum = 0;
    int simil = 0;
    for(int i = 0; i < l1.size();  i++)
    {
        sum += abs(l1[i] - l2[i]);

        simil += l1[i] * counts2[l1[i]];
    }
    cout << sum << endl;
    cout << simil << endl;



}
