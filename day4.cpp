#include <iostream>
#include <map>
#include <set>
#include <cassert>

#include "data.h"

using namespace std;

std::map<char, string> getReplacements()
{
    return {};
}

vector<vector<pair<int, int>>> generate_paths_2(int x)
{
    vector<vector<pair<int, int>>> ret;
    for(int i = 0; i < x - 2; i++)
    {
        for(int j = 0; j < x - 2; j++)
        {
            // horz
            vector<pair<int, int>> path;
            path.push_back({i, j}); // M
            path.push_back({i, j + 2}); // M
            path.push_back({i + 2, j}); // S
            path.push_back({i + 2, j + 2}); // S
            path.push_back({i + 1, j + 1}); // A
            ret.push_back(path);

            path.clear();
            path.push_back({i, j}); // M
            path.push_back({i + 2, j}); // M
            path.push_back({i, j + 2}); // S
            path.push_back({i + 2, j + 2}); // S
            path.push_back({i + 1, j + 1}); // A
            ret.push_back(path);
        }
    }
    return ret;
}

vector<vector<pair<int, int>>> generate_paths(int x)
{
    vector<vector<pair<int, int>>> ret;
    for(int i = 0; i < x - 3; i++)
    {
        for(int j = 0; j < x; j++)
        {
            // horz
            vector<pair<int, int>> path;
            for(int k  = 0; k < 4; k++)
            {
                path.push_back({i + k, j});
            }
            ret.push_back(path);
            reverse(path.begin(), path.end());
            ret.push_back(path);
        }
    }
    for(int i = 0; i < x - 3; i++)
    {
        for(int j = 0; j < x; j++)
        {
            // vert
            vector<pair<int, int>> path;
            for(int k  = 0; k < 4; k++)
            {
                path.push_back({j,  i + k});
            }
            ret.push_back(path);
            reverse(path.begin(), path.end());
            ret.push_back(path);
        }
    }
    for(int i = 0; i < x - 3; i++)
    {
        for(int j = 0; j < x - 3; j++)
        {
            vector<pair<int, int>> path;
            for(int k  = 0; k < 4; k++)
            {
                path.push_back({i + k, j + k});
            }
            ret.push_back(path);
            reverse(path.begin(), path.end());
            ret.push_back(path);
            path.clear();
            for(int k  = 0; k < 4; k++)
            {
                path.push_back({(x - 1) - (i + k), j + k});
            }
            ret.push_back(path);
            reverse(path.begin(), path.end());
            ret.push_back(path);

        }
    }

    return ret;
}

void process(Data& data)
{
    int x = data.raw[0].length();
    int y = data.raw.size();
    int count = 0;
    int count2 = 0;

    assert(x == y);

    auto paths = generate_paths(x);
    for(const auto & p:paths)
    {
        if (data.raw[p[0].first][p[0].second] == 'X'  &&
            data.raw[p[1].first][p[1].second] == 'M'  &&
            data.raw[p[2].first][p[2].second] == 'A'  &&
            data.raw[p[3].first][p[3].second] == 'S')
        {
            count++;
        }
    }
    paths = generate_paths_2(x);
    for(const auto & p:paths)
    {
        if (data.raw[p[0].first][p[0].second] == 'M'  &&
            data.raw[p[1].first][p[1].second] == 'M'  &&
            data.raw[p[2].first][p[2].second] == 'S'  &&
            data.raw[p[3].first][p[3].second] == 'S'  &&
            data.raw[p[4].first][p[4].second] == 'A')
        {
            count2++;
        }
        else if (data.raw[p[0].first][p[0].second] == 'S'  &&
            data.raw[p[1].first][p[1].second] == 'S'  &&
            data.raw[p[2].first][p[2].second] == 'M'  &&
            data.raw[p[3].first][p[3].second] == 'M'  &&
            data.raw[p[4].first][p[4].second] == 'A')
        {
            count2++;
        }
    }
    cout << count << " " << count2 << endl;
}
