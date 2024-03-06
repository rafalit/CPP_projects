#ifndef POSITION_H
#define POSITION_H

#include <utility>  // std::size_t

struct Position
{
    std::size_t x_=0, y_=0;

    Position(unsigned x={}, unsigned y={}): x_(x), y_(y)
    {}

    auto x() const
    {
        return x_;
    }

    auto y() const
    {
        return y_;
    }

    Position& moveUp()
    {
        y_++;
        return *this;
    }
    Position& moveDown()
    {
        y_--;
        return *this;
    }
    Position& moveLeft()
    {
        x_--;
        return *this;
    }
    Position& moveRight()
    {
        x_++;
        return *this;
    }
    Position& moveUpRight()
    {
        return moveUp().moveRight();
    }
};

#endif // POSITION_H
