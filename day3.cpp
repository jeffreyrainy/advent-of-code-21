#include <iostream>
#include <cctype>
#include "data.h"

using namespace std;

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

int mul(const string& s, int pos)
{
    pos += 4;
    int v[2] = {0, 0};
    int cur = 0;

    do
    {
        if (pos == s.length())
        {
            return 0;
        }
        else if (isdigit(s[pos]))
        {
            v[cur] = v[cur] * 10 + (s[pos] - '0');
        }
        else if (s[pos] == ',')
        {
            cur++;
            if (cur > 1) return 0;
        }
        else if (s[pos] == ')')
        {
            return v[0] * v[1];
        }
        else
        {
            return 0;
        }
        pos++;
    }
    while (true);
    return 0;
}

void process(Data& data)
{
    int count = 0;
    int count2 = 0;
    int enabled = 1;
    for(auto s:data.raw)
    {
        int pos = -1;
        int pos1 = -1;
        int pos2 = -1;

        do
        {
            int was = pos;
            pos = s.find("mul(", was + 1);
            pos1 = s.find("do()", was + 1);
            pos2 = s.find("don't()", was + 1);

            if (pos > was && (pos1 < was || pos1 > pos) && (pos2 < was || pos2 > pos))
            {
                int value = mul(s, pos);
                count += value;
                count2 += value * enabled;
            }
            else if (pos1 > was && (pos < was || pos > pos1) && (pos2 < was || pos2 > pos1))
            {
                enabled = 1;
                pos = pos1;
            }
            else if (pos2 > was && (pos < was || pos > pos2) && (pos1 < was || pos1 > pos2))
            {
                enabled = 0;
                pos = pos2;
            }
            else
            {
                break;
            }
        }
        while(pos != -1);
    }
    cout << count << endl;
    cout << count2 << endl;
}
