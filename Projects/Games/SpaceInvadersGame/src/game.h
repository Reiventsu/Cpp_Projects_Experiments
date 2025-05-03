//
// Created by rei on 5/3/25.
//

#pragma once
#include "spaceship.h"

class Game {
public:
    Game();

    ~Game();

    void Draw();

    void Update();

    void ProcessInput();

private:
    SpaceShip spaceShip;
};
