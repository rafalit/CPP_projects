#include "enemy.h"

Enemy::Enemy(Position position, unsigned maxLife): Object(ObjectType::OBJECT_ENEMY, position), maxLife_(maxLife), life_(maxLife)
{}

double Enemy::lifePercent() const
{
    return static_cast<double>(life_) / maxLife_ * 100;
}

bool Enemy::isAlieve() const{
    return life_>0;
}

void Enemy::decreaseLife(unsigned damage)
{
    life_ -= damage;
    if (life_ < 0)
        life_ = 0;
}