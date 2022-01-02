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
    static constexpr const long factor[4] = {1, 10, 100, 1000};

    long cost = 0;

    bool Done() const;
    vector<State<Depth>> GetNext() const;
    void Best() const { cout << *this << endl; };
    bool Accept() const {return true;}

    bool ColReady(long col) const;
    void Simplify();
    long costColInter(long col, long inter, long id) const;
    long costColCol(long colTo, long colFrom) const;

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

template<long Depth>
bool State<Depth>::Done() const
{
    for(long col = 0; col < 4; col++)
    {
        if (cols[col][0] != 'A' + col)
        {
            return false;
        }
    }
    for(long col = 0; col < 4; col++)
    {
        if (!ColReady(col))
        {
            return false;
        }
    }
    return true;
}

template<long Depth>
long State<Depth>::costColInter(long col, long inter, long id) const
{
    long ret = 0;

    if (inter >= col)
    {
        ret = ((inter - col) * 2 + 1 + // side moves
                tops[col]) // get in cost
                * factor[id];
    }
    else
    {
        ret = ((col - inter) * 2 - 1 + // side moves
                tops[col]) // get in cost
                * factor[id];
    }

    return ret;
}

template<long Depth>
long State<Depth>::costColCol(long colTo, long colFrom) const
{
    long ret = (std::abs(colTo - colFrom) * 2 + // side moves
            tops[colTo] + // get in cost
            tops[colFrom] + 1) // get out cost
            * factor[colTo];

    return ret;
}


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
                        long c1 = costColInter(col, si, col);
                        cost += c1;

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
                        long c1 = costColCol(col, si + 1);
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        ++tops[si + 1];
                        changed = true;
                    }
                }
                if (si == 3)
                {
                    if (r[0] == 'A' + col)
                    {
                        long c1 = costColInter(col, 3, col);
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        r[0] = '.';
                        changed = true;
                    }
                    else if (r[1] == 'A' + col && r[0] == '.')
                    {
                        long c1 = costColInter(col, 3, col) + factor[col];
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        r[1] = '.';
                        changed = true;
                    }
                }

                si = col - 1;
                for(; si >= 0; si--)
                {
                    if (inter[si] == 'A' + col)
                    {
                        long c1 = costColInter(col, si, col);
                        cost += c1;

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
                        long c1 = costColCol(col, si);
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        ++tops[si];
                        changed = true;
                    }
                }
                if (si == -1)
                {
                    if (l[0] == 'A' + col)
                    {
                        long c1 = costColInter(col, -1, col);
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        l[0] = '.';
                        changed = true;
                    }
                    else if (l[1] == 'A' + col && l[0] == '.')
                    {
                        long c1 = costColInter(col, -1, col) + factor[col];
                        cost += c1;

                        cols[col][--tops[col]] = 'A' + col;
                        l[1] = '.';
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
                target.cost += target.costColInter(col, si, target.inter[si] - 'A');

                target.Simplify();

                ret.push_back(target);
            }
            if (si == 3) // stack to the right
            {
                target = *this;
                if (r[1] == '.' && r[0] != '.')
                {
                    target.r[1] = r[0];
                    target.r[0] = '.';
                    target.cost += factor[target.r[1] - 'A'];
                }
                if (target.r[0] == '.')
                {
                    target.r[0] = target.cols[col][target.tops[col]];
                    target.tops[col]++;
                    target.cost += target.costColInter(col, 3, target.r[0] - 'A');

                    target.Simplify();

                    ret.push_back(target);
                }
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
                target.cost += target.costColInter(col, si, target.inter[si] - 'A');

                target.Simplify();

                ret.push_back(target);
            }
            if (si == -1) // stack to the left
            {
                target = *this;
                if (l[1] == '.' && l[0] != '.')
                {
                    target.l[1] = l[0];
                    target.l[0] = '.';
                    target.cost += factor[target.l[1] - 'A'];
                }
                if (target.l[0] == '.')
                {
                    target.l[0] = target.cols[col][target.tops[col]];
                    target.tops[col]++;
                    target.cost += target.costColInter(col, -1, target.l[0] - 'A');

                    target.Simplify();

                    ret.push_back(target);
                }
            }
        }
    }

    return ret;
}

void process(Data& data)
{
    State<2> start;
    State<4> start4;

    for(long i = 0; i < 4; i++)
    {
        start.cols[i][0] = data.words[2][0][i];
        start.cols[i][1] = data.words[3][0][i];
    }

    Explorer<State<2>> e;
    e.Explore(start);


    for(long i = 0; i < 4; i++)
    {
        start4.cols[i][0] = data.words[2][0][i];
        start4.cols[i][3] = data.words[3][0][i];
    }

    start4.cols[0][1] = 'D';
    start4.cols[1][1] = 'C';
    start4.cols[2][1] = 'B';
    start4.cols[3][1] = 'A';

    start4.cols[0][2] = 'D';
    start4.cols[1][2] = 'B';
    start4.cols[2][2] = 'A';
    start4.cols[3][2] = 'C';

    Explorer<State<4>> e4;
    e4.Explore(start4);

}
