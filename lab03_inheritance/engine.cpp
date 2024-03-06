#include <algorithm>
#include "engine.h"
#include "player.h"
#include "stage.h"
#include "shoot.h"
#include "enemy.h"


namespace {
inline auto signum(int x)
{
    return (x > 0) - (x < 0);
}

Direction randDirection()
{
    auto randEdge = rand() % static_cast<uint8_t>(Direction::UPPER_LEFT);
    return static_cast<Direction>(randEdge);
}
} // namespace


Position generateNewEnemyPosition(int width, int height)
{
    Position position2Generate = Position(rand() % width, rand() % height);

    switch (randDirection()) {
        case Direction::UP:
            position2Generate.y_ = height-1;
            break;
        case Direction::DOWN:
            position2Generate.y_ = 0;
            break;
        case Direction::LEFT:
            position2Generate.x_ = 0;
            break;
        case Direction::RIGHT:
            position2Generate.x_ = width-1;
            break;
        default:
            break;
    }
    return position2Generate;
}


Engine::~Engine() = default;



Engine::Engine(std::size_t stageWidth, std::size_t stageHeight):
    player_(new Player), stage_(new Stage(stageWidth, stageHeight))
{
    // TODO...
}

void Engine::update()
{
    updateBullets();
    updateEnemies();
    randEnemies();
}

void Engine::updateBullets()
{
    // TODO...
}

void Engine::updateEnemies()
{
    // TODO...
}

void Engine::movePlayerUp()
{
    Position playerPos = player_->position();
    playerPos.moveUp();
    player_->setPosition(playerPos);
}

void Engine::movePlayerDown()
{

    Position playerPos = player_->position();
    playerPos.moveDown();
    player_->setPosition(playerPos);
}

void Engine::movePlayerLeft()
{
    Position playerPos = player_->position();
    playerPos.moveLeft();
    player_->setPosition(playerPos);
}
void Engine::movePlayerRight()
{
    Position playerPos = player_->position();
    playerPos.moveRight();
    player_->setPosition(playerPos);
}

void Engine::playerShoots()
{
    Position playerPos = player_->position();
    Direction playerDir = player_->direction();

    Shoot shoot(playerDir, playerPos);

    shoots_.push_back(shoot);
}

Position Engine::playerPosition() const
{
    Position playerPos = player_->position();
    return playerPos;
}

Direction Engine::playerDirection() const
{
    Direction playerDir = player_->direction();
    return playerDir;
}

bool Engine::isPlayerAlieve() const
{
    bool isAlieve = player_->isAlieve();
    return isAlieve;
}

std::size_t Engine::stageWidthCells() const
{

    return stage_->width();
}
std::size_t Engine::stageHeightCells() const
{
    return stage_->height();
}

void Engine::randEnemies(Position (*positionGenerator)(int,int))
{
    if (enemies_.size() < maxEnemies_)
    {
        Position pos = positionGenerator(stage_->width(), stage_->height());
        enemies_.push_back(std::make_shared<Enemy>(pos));
    }
}
