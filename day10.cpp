#include <iostream>
#include "data.h"
#include <stack>

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{};
    return ret;
}

long process(std::string s, long& total2)
{
    total2 = 0;
    std::stack<char> st;

    for(auto c:s)
    {
        switch(c)
        {
            case '[':
            case '{':
            case '(':
            case '<':
                st.push(c);
            break;
            default:
                char c0 = st.top();
                st.pop();
                if ((c - c0 != 1) && (c - c0 != 2))
                {
                    return c == ')' ? 3 : c == ']' ? 57 : c == '}' ? 1197 : 25137;
                }
            break;
        }
    }
    while (!st.empty())
    {
        total2 *= 5;
        char c0 = st.top();
        st.pop();
        total2 += (c0 == '(' ? 1 : c0 == '[' ? 2 : c0 == '{' ? 3 : 4);
    }
    return 0;
}

void process(Data& data)
{
    long total = 0;
    long total2 = 0;
    std::vector<long> totals2;
    for(auto l:data.words)
    {
        auto s = l[0];
        total += process(s, total2);
        if (total2) totals2.push_back(total2);
    }
    std::cout << total << std::endl;

    std::sort(totals2.begin(), totals2.end());
    std::cout << totals2[totals2.size() / 2] << std::endl;
}
