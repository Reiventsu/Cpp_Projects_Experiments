//
// Created by rei on 5/3/25.
//

#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"

class Game {
public:
    Game();

    ~Game();

    void Draw();

    void Update();

    void ProcessInput();

private:
    void KillInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    SpaceShip spaceShip;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;

};
