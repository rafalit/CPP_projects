#include "circle.h"
#include<math.h>
namespace Shapes{
    int Circle::x() const{
        return center.x_;
    }
    int Circle::y() const{
        return center.y_;
    }
    int Circle::getRadius() const{
        return radius_;
    }

    Circle::Circle(int xCenter, int yCenter, int radius) : center{xCenter, yCenter}, radius_(radius) {

    }

    bool Circle::isIn(int x, int y)const {
        double distance = std::sqrt(std::pow(x - center.x_, 2) + std::pow(y - center.y_, 2));
        if (distance <= radius_){
            return true;}
        else{
        return false;}
        }



}