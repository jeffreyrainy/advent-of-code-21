#include <iostream>
#include <cctype>
#include "data.h"

using std::map, std::string, std::set, std::multimap;

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'-', " "}};
    return ret;
}

multimap<string, string> paths;
long count = 0;
std::string twice = "";

void recurse(string start, map<string, long>& visited)
{
    for(auto it = paths.lower_bound(start); it != paths.upper_bound(start); it++)
    {
        if (it->second != "end" && (std::isupper(it->second[0]) || visited[it->second] == 0))
        {
            visited[it->second]++;
            recurse(it->second, visited);
            visited[it->second]--;
        }

        if (it->second == "end")
        {
            count++;
        }
    }
}

void recurse2(string start, map<string, long>& visited)
{
    for(auto it = paths.lower_bound(start); it != paths.upper_bound(start); it++)
    {
        if (it->second != "end" && (std::isupper(it->second[0]) || visited[it->second] == 0))
        {
            visited[it->second]++;
            recurse2(it->second, visited);
            visited[it->second]--;
        }
        else if (it->second != "end" && (std::isupper(it->second[0]) || visited[it->second] == 1) && (twice == "") && it->second != "start")
        {
            twice = it->second;
            visited[it->second]++;
            recurse2(it->second, visited);
            visited[it->second]--;
            twice = "";
        }

        if (it->second == "end")
        {
            count++;
        }
    }
}


void process(Data& data)
{
    for(long i = 0; i < data.words.size(); i++)
    {
        paths.insert(std::make_pair(data.words[i][0], data.words[i][1]));
        paths.insert(std::make_pair(data.words[i][1], data.words[i][0]));
    }

    count = 0;
    std::map<string, long> empty;
    empty.insert({"start", 1});

    recurse("start", empty);
    std::cout << count << std::endl;

    count = 0;
    empty.clear();
    empty.insert({"start", 1});

    recurse2("start", empty);
    std::cout << count << std::endl;
}
