//
// Created by rei on 5/3/25.
//

#pragma once
#include "raylib.h"
#include "laser.h"
#include <vector>

class SpaceShip {
public:
    SpaceShip();

    ~SpaceShip();

    void Draw();

    void MoveLeft();

    void MoveRight();

    void FireLaser();

    void ResetPlayerShip();

    Rectangle getRect();

    std::vector<Laser> lasers;

private:
    Texture2D image{};
    Vector2 position{};
    double lastFireTime{};
};
