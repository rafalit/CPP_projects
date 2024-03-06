# Dziedziczenie i interakcje między obiektami w formie gierki
W zadaniu chodzi o to, aby poćwiczyć używanie klas, ale też stosowanie dziedziczenia w programowaniu. Poza tym też interakcje między obiektami - a wszystko na przykładzie gierki 2D.

### Utrudnienie - makra preprocesora
Zadanie zawiera testy automatyczne, które testują czy dana metoda jest zaimplementowana poprawnie. Jeśli metody nie ma a byłaby testowana to byłby błąd kompilacji. Tym samym zadanie można by oddać wyłącznie jako wszystko lub jako nic. Dlatego też korzystam z makr preprocesora, które zależnie od tego czy dana funkcjonalność jest zaimplementowana czy nie aktywują (w trakcie kompilacji) odpowiednie części kodu.


Treść do wykonania:
---------
### Klasa `Object`:
Proszę o zaimplementowanie klasy `Object`, która będzie miała trzymała typ obiektu (zdefiniowany `ObjectType`), oraz pozycje (zdefiniowany `Position`).
Zaimplementuj metody:
- Konstruktor przyjmujący `ObjectType` i `Position` (pozycja niech ma wartość domyślną)
- gettery `type()` i `position()`
- następnie można usunąć: `UNIMPLEMENTED_objectWithConstructorAndGetters`
- setter `setPosition`, następnie można usunąć `UNIMPLEMENTED_objectSetPosition`
- metody do poruszania obiektem o jedną komórkę: `moveUp()`, `moveDown()`, `moveLeft()`, `moveRight()`, następnie można usunąć `UNIMPLEMENTED_movingObject`
   1. co zyskali byśmy gdyby `moveX()` zwracało `*this`?

### Klasa `Player` (dziedzicząca po `Object`):
Proszę o utworzenie klasy `Player`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_playerIsObject`
- Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter. Domyślna wartość to `Direction::RIGHT`
   - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerHasDirection`
- Klasa powinna mieć składową oznaczającą czy gracz żyje, oraz getter i setter: `isAlieve()`, `setIsAlieve()`
   - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerCanDie`

### Klasa `Shoot` (dziedzicząca po `Object`):
Proszę o utworzenie klasy `Shoot`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_shootIsObject`
- Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter
- Klasa powinna mieć konstruktor przyjmujący kierunek i pozycje początkową
- Po zaimplementowania tego proszę zakomentować `UNIMPLEMENTED_shootHasDirectionAndPosition`
- Klasa powinna zawierać statyczny atrybut odpowiadający prędkości o wartości `2`, oraz getter `speed()`

### Klasa `Enemy` (dziedzicząca po `Object`):
Proszę o utworzenie klasy `Enemy`, która będzie dziedziczyć po klasie `Object`
- Klasa ta powinna mieć mieć składową odpowiadającą ilości punktów życia, oraz getter: `lifePercent()`
- Klasa powinna mieć konstruktor przyjmujący aktualną pozycje oraz maksymalne życie z wartością domyślną.
- Klasa powinna mieć metodę `isAlieve()` która zwraca prawdę jeśli wróg ma życie powyżej zera
- Klasa powinna mieć metodę `decreaseLife()` przyjmującą jako argument liczbę obrażeń
- Po zaimplementowaniu powyższego proszę zakomentować makro `UNIMPLEMENTED_enemy`

### Klasa Engine - główny silnik gry:
Proszę o zaimplementowanie klasy `Engine`, która będzie zarządzać obiektami, oraz będzie interfejsem do komunikacji z GUI.
- Szczegółowy opis poszczególnych metod znajduje się nad metodami.
- Nie są napisane testy dla całej klasy, więc możliwe jest przejście wszystkich testów, ale gra nie będzie działać.
- Można otrzymać punkty z aktywności za te zajęcia za uruchomienie gry i pokazanie mi, to na następny raz
- Oto metody do zaimplementowania z pliku `engine.h`:
```c++
class Engine
{
public:
    /// Konstruktor, który dokona odpowiednich inicjalizacji
    Engine(std::size_t stageWidth, std::size_t stageHeight);

    /// Destruktor (jeśli trzeba)
    ~Engine();

    /// metody zwracające informacje o rozmiarze planszy
    std::size_t stageWidthCells() const;
    std::size_t stageHeightCells() const;

    /// zakomentowac makro: UNIMPLEMENTED_engineConstructedWithWidthAndHeight

    /// metody zwracające informacje na temat gracza
    Position playerPosition() const; /// domyslnie srodek planszy
    Direction playerDirection() const; /// domyślnie Direction::RIGHT
    bool isPlayerAlieve() const;

    /// zakomentowac makro: UNIMPLEMENTED_engineHasGettersToGetInformationAboutPlayer

    /// metody obsługiwane z klawiatury
    void playerShoots();
    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    /// zakomentowac makro: UNIMPLEMENTED_engineCanMovePlayer

    /// metody zwracające informacje na temat obiektów w grze
    const std::vector<Shoot>& shoots() const
    {
        return shoots_;
    }

    /// zakomentowac makro: UNIMPLEMENTED_engineHandlePlayerShooting

    /// metoda wywoływania kilka razy na sekundę, która ma za zadanie zaktualizowanie obiektów
    void update();

    const auto& enemies() const
    {
        return enemies_;
    }

protected:
    /// metoda, która doda określoną liczbę wrogów w miejscach zwróconych przez generator:
    void randEnemies(Position (*positionGenerator)(int, int)=generateNewEnemyPosition);
    /// metoda, która wpierw usunie zabitych wrogów, a następnie wykona ruch
    void updateEnemies();

    /// zakomentuj makro: UNIMPLEMENTED_engineHandlesEnemies

    /// metoda, która powinna zaktualizować pociski, czyli przesunąć je,
    /// obsłużyć trafienie wroga lub wyjście poza scenę
    void updateBullets();
```
## Project Structure

      .
      ├── lab3inheritance           # directory containing exercises
      │   ├── CMakeLists.txt        # CMake configuration file - the file is to open out project in our IDE
      │   ├── enemy.h
      │   ├── enemy.cpp
      │   ├── engine.h
      │   ├── engine.cpp
      │   ├── direction.h
      │   ├── Dockerfile
      │   ├── game                  # inner CMake for game in QT (qt libraries must be installed)
      │   │   ├── background.png
      │   │   ├── bibliography.txt
      │   │   ├── bullet.png
      │   │   ├── CMakeLists.txt
      │   │   ├── enemy.png
      │   │   ├── gameMain.cpp
      │   │   ├── mainwindow.cpp
      │   │   ├── mainwindow.h
      │   │   ├── mainwindow.ui
      │   │   ├── music.mp3
      │   │   ├── player.png
      │   │   └── resources.qrc
      │   ├── main.cpp              # main file - here we can test out solution manually, but it is not required
      │   ├── object.h
      │   ├── object.cpp
      │   ├── player.h
      │   ├── position.h
      │   ├── shoot.h
      │   ├── stage.h
      │   ├── stage.cpp
      │   ├── README.md             # this file
      │   └── tests                 # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
      │       ├── CMakeLists.txt    # inner CMake for tests - it is included by outter CMake
      │       ├── engineTests.cpp
      │       ├── objectTests.cpp
      │       ├── playerTests.cpp
      │       ├── shootTests.cpp
      │       └── lib               # directory containing GTest library
