#include "object.h"



ObjectType Object::type() const
{
    return type_;
}

Position Object::position() const
{
    return position_;
}

Object::Object(ObjectType type, Position position): type_(type), position_(position)
{}


void Object::setPosition(Position position)
{
    position_ = position;
}

void Object :: moveUp(){
     position_.moveUp();
}

void Object :: moveDown(){
    position_.moveDown();
}

void Object :: moveRight(){
    position_.moveRight();
}

void Object :: moveLeft(){
    position_.moveLeft();
}

