#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint> // uint8_t

enum class Direction : uint8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPPER_LEFT,
    UPPER_RIGHT,
    DOWNER_LEFT,
    DOWNER_RIGHT,
    CENTER,
    INMOVABLE,
    UNKNOWN
};

#endif // DIRECTION_H
