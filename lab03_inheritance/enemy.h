#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

/**
 * Proszę o utworzenie klasy `Enemy`, która będzie dziedziczyć po klasie `Object`
 * - Klasa ta powinna mieć mieć składową odpowiadającą ilości punktów życia, oraz getter: `lifePercent()`
 * - Klasa powinna mieć konstruktor przyjmujący aktualną pozycje oraz maksymalne życie z wartością domyślną.
 * - Klasa powinna mieć metodę `isAlieve()` która zwraca prawdę jeśli wróg ma życie powyżej zera
 * - Klasa powinna mieć metodę `decreaseLife()` przyjmującą jako argument liczbę obrażeń
 * - Po zaimplementowaniu powyższego proszę zakomentować makro `UNIMPLEMENTED_enemy`
 */



class Enemy : public Object
{
protected:
    unsigned life_;
    unsigned maxLife_;

public:
    Enemy(Position position, unsigned maxLife = 100);

    double lifePercent() const;

    bool isAlieve() const;

    void decreaseLife(unsigned damage);

};

#endif // ENEMY_H
