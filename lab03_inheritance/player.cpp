//
// Created by szaro on 25.03.2023.
//
#include "player.h"

Player::Player(ObjectType type, Position position, Direction direction)
        : Object(type, position), direction_(direction), isAlive_(true)
{
}

Direction Player::direction()
{
    return direction_;
}

void Player::setDirection(Direction direction)
{
    direction_ = direction;
}

bool Player::isAlieve() const
{
    return isAlive_;
}

void Player::setIsAlieve(bool isAlive)
{
    isAlive_ = isAlive;
}