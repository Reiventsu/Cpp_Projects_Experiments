//
// Created by rei on 5/3/25.
//

#pragma once
#include "spaceship.h"
#include "obstacle.h"

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
    SpaceShip spaceShip;
    std::vector<Obstacle> obstacles;
};
