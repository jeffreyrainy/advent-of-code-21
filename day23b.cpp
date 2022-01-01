#include <iostream>
#include <array>
#include "data.h"
#include "explorer.h"

using std::string;
using std::array;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::ostream;

map<char, string> getReplacements()
{
    map<char, string> ret{{'#', ""}};
    return ret;
}

template<long Depth>
class State
{
public:

    array<array<char, Depth>, 4> cols;
    array<long, 4> tops = {0}; // index of top of each columns. [0] is top
    char inter[3] = {'.', '.', '.'}; // spots between columns
    char l[2] = {'.', '.'}; // two leftmost spots, [0] most accessible
    char r[2] = {'.', '.'}; // two rightmost spots, [0] most accessible

    long cost = 0;

    bool Done() const {return false;}
    vector<State<Depth>> GetNext() const;
    void Best() const {};
    bool Accept() const {return true;}

    bool ColReady(long col) const;
    void Simplify();
};

template<long Depth>
ostream& operator<<(ostream& out, const State<Depth>& s)
{
    out << "(" << s.cost << ")\n";

    out << s.l[1] << s.l[0] << " " << s.inter[0] << " " << s.inter[1] << " " << s.inter[2] << " " << s.r[0] << s.r[1] << endl;

    for(long i = 0; i < Depth; i++)
    {
        out << "  "
            << (s.tops[0] <= i ? s.cols[0][i] : '.')
            << " "
            << (s.tops[1] <= i ? s.cols[1][i] : '.')
            << " "
            << (s.tops[2] <= i ? s.cols[2][i] : '.')
            << " "
            << (s.tops[3] <= i ? s.cols[3][i] : '.')
            << endl;
    }
    out << "  "
        << (s.ColReady(0) ? 'R' : ' ')
        << " "
        << (s.ColReady(1) ? 'R' : ' ')
        << " "
        << (s.ColReady(2) ? 'R' : ' ')
        << " "
        << (s.ColReady(3) ? 'R' : ' ')
        << endl;

    return out;
}

//
//  0 1 2
// 0 1 2 3

template<long Depth>
bool State<Depth>::ColReady(long col) const
{
    for(long i = tops[col]; i < Depth; i++)
    {
        if (cols[col][i] != 'A' + col)
        {
            return false;
        }
    }
    return true;
}

//todo: bump L0 to L1 and R0 to R1

template<long Depth>
void State<Depth>::Simplify()
{
    bool changed;

    do
    {
        changed = false;
        for(long col = 0; col < 4; col++)
        {
            if (ColReady(col))
            {
                long si = col;
                for(; si < 3; si++)
                {
                    if (inter[si] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        inter[si] = '.';
                        changed = true;
                    }
                    else if (inter[si] != '.')
                    {
                        break;
                    }
                    if (tops[si + 1] != Depth && cols[si + 1][tops[si + 1]] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        ++tops[si + 1];
                        changed = true;
                    }
                }
                if (si == 3)
                {
                    if (r[0] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        r[0] = '.';
                        changed = true;
                    }
                }

                si = col - 1;
                for(; si >= 0; si--)
                {
                    if (inter[si] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        inter[si] = '.';
                        changed = true;
                    }
                    else if (inter[si] != '.')
                    {
                        break;
                    }
                    if (tops[si] != Depth && cols[si][tops[si]] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        ++tops[si];
                        changed = true;
                    }
                }
                if (si == -1)
                {
                    if (l[0] == 'A' + col)
                    {
                        cols[col][--tops[col]] = 'A' + col;
                        l[0] = '.';
                        changed = true;
                    }
                }
            }
        }
    }
    while(changed);



}


template<long Depth>
vector<State<Depth>> State<Depth>::GetNext() const
{
    vector<State<Depth>> ret;
    State<Depth> target;

    for(long col = 0; col < 4; col++)
    {
        if ((tops[col] != Depth) && !ColReady(col))
        {
            // Out to the right
            long si = col;
            for(; si < 3; si++)
            {
                if (inter[si] != '.')
                {
                    break;
                }
                target = *this;
                target.inter[si] = target.cols[col][target.tops[col]];
                target.tops[col]++;

                target.Simplify();

                ret.push_back(target);
            }
            if (si == 3) // stack to the right
            {
                if (r[0] == '.')
                {
                    target = *this;
                    target.r[0] = target.cols[col][target.tops[col]];
                    target.tops[col]++;

                    target.Simplify();

                    ret.push_back(target);
                }
                // deal with two element stacked
            }
            // out to the left
            si = col - 1;
            for(; si >= 0; si--)
            {
                if (inter[si] != '.')
                {
                    break;
                }
                target = *this;
                target.inter[si] = target.cols[col][target.tops[col]];
                target.tops[col]++;

                target.Simplify();

                ret.push_back(target);
            }
            if (si == -1) // stack to the left
            {
                if (l[0] == '.')
                {
                    target = *this;
                    target.l[0] = target.cols[col][target.tops[col]];
                    target.tops[col]++;

                    target.Simplify();

                    ret.push_back(target);
                }
                // deal with two element stacked
            }
        }
    }

    cout << "=======" << endl;
    cout << *this << endl;

    for(const auto& s:ret)
    {
        cout << s << endl;
    }

    cout << endl;


    return ret;
}

void process(Data& data)
{
    State<2> start;

/*
    start.cols[0][0] = 'X';
    start.cols[0][1] = 'X';

    start.cols[1][0] = 'D';
    start.cols[1][1] = 'D';

    start.cols[2][0] = 'A';
    start.cols[2][1] = 'B';

    start.cols[3][0] = 'C';
    start.cols[3][1] = 'B';

    start.inter[0] = 'A';
    start.l[0] = 'C';

    start.tops[0] = 2;

    cout << start << endl;

    cout << start.ColReady(0) << endl;
    start.Simplify();

    cout << start << endl;
*/


    for(long i = 0; i < 4; i++)
    {
        start.cols[i][0] = data.words[2][0][i];
        start.cols[i][1] = data.words[3][0][i];
    }

    cout << start << endl;

    Explorer<State<2>> e;
    e.Explore(start);

}
