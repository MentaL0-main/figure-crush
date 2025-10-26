#pragma once

#include <raylib.h>

struct Figure
{
    Figure(Rectangle r, unsigned short t, Color c)
    {
        rect = r;
        type = t;
        color = c;
    }

    Rectangle rect;
    unsigned short type;
    Color color;
};