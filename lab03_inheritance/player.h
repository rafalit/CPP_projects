#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "direction.h"

/**
 * Proszę o utworzenie klasy `Player`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_playerIsObject`
 * - Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter. Domyślna wartość to `Direction::RIGHT`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerHasDirection`
 * - Klasa powinna mieć składową oznaczającą czy gracz żyje, oraz getter i setter: `isAlieve()`, `setIsAlieve()`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerCanDie`
 */



class Player : public Object
{
protected:
    Direction direction_;
    bool isAlive_;

public:
    Direction direction();
    void setDirection(Direction direction);

    Player(ObjectType type = ObjectType::OBJECT_PLAYER, Position position = Position(), Direction direction = Direction::RIGHT);

    bool isAlieve() const;
    void setIsAlieve(bool isAlive);
};

#endif // PLAYER_H

