#include <iostream>

#include <queue>
#include "data.h"
#include "explorer.h"

using std::string;

class State
{
public:

// #############
// #01 2 3 4 56#
// ###0#1#2#3###
//   #4#5#6#7#
//   #########

    string hallway = ".......";
    string room = "ABCDABCD";

    long cost = 0;

    std::vector<State> GetNext();
    bool Done() const { return (room == "ABCDABCD"); }
    void Best() const;
    bool Accept() const;

    bool operator<(const State& that) const;

    static long best;
    static long count;
    static std::map<State, long> bestState;
//    string history;
};

bool State::operator<(const State& that) const
{
    return ((that.hallway < hallway) ||
            (that.hallway == hallway && that.room < room));
}

std::map<State, long> State::bestState;
long State::best = 0;
long State::count = 0;

std::ostream& operator<<(std::ostream& out, const State& s)
{
    out << "(" << s.cost << ")\n";
    out << s.hallway.substr(0,2) << " " << s.hallway[2] << " " << s.hallway[3] << " " << s.hallway[4] << " " << s.hallway.substr(5, 2) << std::endl;
    out << "  " << s.room[0] << " " << s.room[1] << " " << s.room[2] << " " << s.room[3] << " " << std::endl;
    out << "  " << s.room[4] << " " << s.room[5] << " " << s.room[6] << " " << s.room[7] << " " << std::endl;

    return out;
}

bool State::Accept() const
{
    if (best && cost > best)
    {
        return false;
    }

    if ((hallway[2] == 'D' && hallway[4] == 'A') ||
        (hallway[3] == 'D' && hallway[4] == 'A') ||
        (hallway[2] == 'D' && hallway[3] == 'A') ||
        (hallway[2] == 'C' && hallway[3] == 'A') ||
        (hallway[3] == 'D' && hallway[4] == 'B'))
    {
        return false;
    }

    if (bestState.find(*this) != bestState.end() &&
        bestState[*this] < cost)
    {
        return false;
    }

    bestState[*this] = cost;

    count++;
    return true;
}

void State::Best() const
{
    best = cost;
    std::cout << *this << std::endl;
}

std::vector<State> State::GetNext()
{
    std::vector<State> ret;

    long hpos[] = {0,1,3,5,7,9,10};
    long rpos[] = {2,4,6,8};
    long costs[] = {1,10,100,1000};

    for(int r = 0; r < 8; r++) // room position
    {
        if ((r > 3) && (room[r - 4] != '.'))
        {
            // can't jump over room occupant
            continue;
        }
        if ((room[r] == '.') && (r < 4) && room[r + 4] != ('A' + r))
        {
            // can't go into outer room if inner room not ok
            continue;
        }
        if ((r < 4) && (room[r] == ('A' + r)) && (room[r + 4] == ('A' + r)))
        {
            // can't move out of outer room if full room is OK
            continue;
        }
        if ((r >= 4) && (room[r] == ('A' + r - 4)))
        {
            // can't move out of inner room if correct
            continue;
        }

        for(int h = 0; h < 7; h++) // hallway position
        {
            if ((room[r] == '.') == (hallway[h] == '.'))
            {
                // must switch an occupied and free spot
                continue;
            }
            if ((room[r] == '.') && hallway[h] != ('A' + (r % 4)))
            {
                // can't go into wrong room
                continue;
            }

            if (((hallway[1] != '.') && (h == 0)) ||
                ((hallway[5] != '.') && (h == 6)))
            {
                // can't jump over hallway 1 or 5
                continue;
            }
            if ((hallway[2] != '.') && (h != 2) && (h > 2) != ((r%4) > 0))
            {
                // can't jump over hallway 2
                continue;
            }
            if ((hallway[3] != '.') && (h != 3) && (h > 3) != ((r%4) > 1))
            {
                // can't jump over hallway 3
                continue;
            }
            if ((hallway[4] != '.') && (h != 4) && (h > 4) != ((r%4) > 2))
            {
                // can't jump over hallway 4
                continue;
            }
            State s = *this;
            std::swap(s.hallway[h], s.room[r]);

            long moves =
                (r / 4) + // one move from the last row
                1 + // one move into hallway
                std::abs(hpos[h] - rpos[r % 4]); // number of hallway steps

            s.cost += moves * costs[hallway[h] + room[r] - '.' - 'A'];

    //        s.history = history + ' ' + char(h + '0') + char(r + '0');
    //        std::cout << "Going from " << *this;
    //        std::cout << "to " << s << std::endl;

            ret.push_back(s);
        }
    }

    return ret;
}

std::map<char, string> getReplacements()
{
    std::map<char, string> ret{{'#', ""}};
    return ret;
}

void process(Data& data)
{
    State s;
    Explorer<State> exp;

    s.count = 0;
    s.room = data.words[2][0] + data.words[3][0];
    s.cost = 0;

    State f = exp.Explore(s);
    std::cout << f << std::endl;
    std::cout << f.count << std::endl;

//    std::cout << f.history << std::endl;
}
