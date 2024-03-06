//
// Created by szaro on 04.04.2023.
//

#include "rectangle.h"

namespace Shapes {

    Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo)
            :  diagonal1{xFrom, yFrom}, diagonal2{xTo, yTo}{}

            //////////////////////////////
    int Rectangle::x() const{
        return diagonal1.x_;
    }
    int Rectangle::y() const{
        return diagonal1.y_;
    }
    int Rectangle::xTo() const{
        return diagonal2.x_;
    }
    int Rectangle::yTo() const{
        return diagonal2.y_;
    }

    bool Rectangle::isIn(int x, int y) const {
        if (x >= diagonal1.x_ && x <= diagonal2.x_ && y >= diagonal1.y_ && y <= diagonal2.y_) {
            return true;
        } else {
            return false;
        }

    }
}