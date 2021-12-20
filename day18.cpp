#include <iostream>
#include "data.h"

using std::string;

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'[', " [ "}, {']', " ] "}, {',', " , "}};
    return ret;
}

class SnailFish
{
public:
    SnailFish() {};
    SnailFish(const SnailFish&) = default;
    SnailFish(std::vector<string> numbers, long pos, long& outPos);

    SnailFish operator+(const SnailFish& that);
    void reduce();
    void reduceRec(long);
    void split();

    long magnitude();

    long value = 0;
    SnailFish* left = nullptr;
    SnailFish* right = nullptr;
    static SnailFish* lastRegular;
    static SnailFish* exploding;

};

SnailFish* SnailFish::lastRegular = nullptr;
SnailFish* SnailFish::exploding = nullptr;

std::ostream& operator<<(std::ostream& out, const SnailFish& snail)
{
    if (snail.left)
    {
        out << "[" << *snail.left << "," << *snail.right << "]";
    }
    else
    {
        out << snail.value;
    }
    return out;
}

void SnailFish::split()
{
    if (left)
    {
        left->split();
        right->split();
    }
    else
    {
        if (value > 9)
        {
            left = new SnailFish();
            right = new SnailFish();

            left->value = value / 2;
            right->value = value - left->value;
            value = 0;

            throw(0);
        }
    }
}

void SnailFish::reduceRec(long depth)
{
    if (depth == 4 && left && !exploding)
    {
        if (lastRegular)
        {
            lastRegular->value += left->value;
        }

        exploding = this;
        return;
    }
    if (exploding && !left)
    {
        value += exploding->right->value;
        throw(0);
    }

    if (left)
    {
        left->reduceRec(depth + 1);
    }
    if (!exploding && !left && !right)
    {
        lastRegular = this;
    }
    if (right)
    {
        right->reduceRec(depth + 1);
    }
}

void SnailFish::reduce()
{
    bool again;
    do
    {
        again = false;

        lastRegular = nullptr;
        exploding = nullptr;
        try
        {
            reduceRec(0);
        }
        catch(...){}

        if (exploding)
        {
            exploding->left = nullptr;
            exploding->right = nullptr;
            exploding->value = 0;
            again = true;
        }
        else
        {
            try
            {
                split();
            }
            catch(...) { again = true; }
        }
    }
    while(again);
}

SnailFish::SnailFish(std::vector<string> numbers, long pos, long& outPos)
{
    if (numbers[pos] == "[")
    {
        left = new SnailFish(numbers, pos + 1, outPos);
        pos = outPos;

        assert(numbers[pos] == ",");

        right = new SnailFish(numbers, pos + 1, outPos);
        pos = outPos;

        assert(numbers[pos] == "]");

        outPos ++;
    }
    else
    {
        value = std::stol(numbers[pos]);
        outPos = pos + 1;
    }
}

SnailFish SnailFish::operator+(const SnailFish& that)
{
    SnailFish ret;
    ret.left = new SnailFish(*this);
    ret.right = new SnailFish(that);
    return ret;
}

long SnailFish::magnitude()
{
    if (left)
    {
        return 3 * left->magnitude() + 2 * right->magnitude();
    }
    return value;
}


void process(Data& data)
{
    long pos;

    SnailFish s;

    for(long i=0; i < data.words.size(); i++)
    {
        if (!i)
        {
            s = SnailFish{data.words[i], 0, pos};
        }
        else
        {
            s = s + SnailFish{data.words[i], 0, pos};
        }
        s.reduce();
    }
    std::cout << s.magnitude() << std::endl;

    long best = 0;
    for(long i=0; i < data.words.size(); i++)
    for(long j=0; j < data.words.size(); j++)
    {
        if (i != j)
        {
            s = SnailFish{data.words[i], 0, pos} + SnailFish{data.words[j], 0, pos};
            s.reduce();
            if (s.magnitude() > best)
            {
                best = s.magnitude();
            }
        }
    }
    std::cout << best << std::endl;

}
