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

    void Draw() const;

    void MoveLeft();

    void MoveRight();

    void FireLaser();

    void ResetPlayerShip();

    [[nodiscard]] Rectangle getRect() const;

    std::vector<Laser> lasers;

private:
    Texture2D image{};
    Vector2 position{};
    double lastFireTime{};
};
