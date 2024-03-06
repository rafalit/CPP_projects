//
// Created by szaro on 25.03.2023.
//
#include "shoot.h"

void Shoot::setDirection(Direction direction)
{
    direction_ = direction;
}

Direction Shoot::direction() const
{
    return direction_;
}

Shoot::Shoot(Direction direction, Position position)
        : Object(ObjectType::OBJECT_SHOOT, position), direction_(direction)
{
}

int Shoot::speed()
{
    return speed_;
}






