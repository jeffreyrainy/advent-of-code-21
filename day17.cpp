#include <iostream>
#include "data.h"

std::map<char, std::string> getReplacements()
{
    std::map<char, std::string> ret{{'.'," "}, {','," "}, {'='," "}, {'x'," "}, {'y'," "}};
    return ret;
}

void process(Data& data)
{
    long x0 = data.numbers[0][2];
    long x1 = data.numbers[0][3];
    long y0 = data.numbers[0][4];
    long y1 = data.numbers[0][5];

    long bestMaxY = 0;
    long bestX = 0;
    long bestY = 0;
    long count = 0;

    for(long vx0 = 1; vx0 < 1000; vx0++)
    for(long vy0 = -1000; vy0 < 1000; vy0++)
    {
        long x = 0;
        long y = 0;
        long maxy = 0;
        long vx = vx0, vy = vy0;
        bool hit = false;

        for(long step = 0; step < 1000; step++)
        {
            x += vx;
            y += vy;
            vx = vx - ((vx > 0) ? 1 : 0);
            vy -= 1;

            maxy = (y > maxy) ? y : maxy;

            if (x >= x0 && x <= x1 && y >= y0 && y <= y1)
            {
                hit = true;
                count++;
                break;
            }
        }

        if (hit && maxy > bestMaxY)
        {
            bestMaxY = maxy;
            bestX = vx0;
            bestY = vy0;
        }
    }

    std::cout << bestMaxY << " " << count << std::endl;




}
