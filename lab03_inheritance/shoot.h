#ifndef SHOOT_H
#define SHOOT_H

#include "object.h"
#include "direction.h"


/**
 * Proszę o utworzenie klasy `Shoot`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_shootIsObject`
 * - Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter
 * - Klasa powinna mieć konstruktor przyjmujący kierunek i pozycje początkową
 * - Po zaimplementowania tego proszę zakomentować `UNIMPLEMENTED_shootHasDirectionAndPosition`
 * - Klasa powinna zawierać statyczny atrybut odpowiadający prędkości o wartości `2`, oraz getter `speed()`
 */





class Shoot : public Object
{
protected:
    Direction direction_;
    static const int speed_ = 2;

public:
    void setDirection(Direction direction);
    Direction direction() const;

    Shoot(Direction direction = Direction::RIGHT, Position position = Position());

    static int speed();
};

#endif // SHOOT_H
