//
// Created by rei on 5/3/25.
//

#pragma once
#include "raylib.h"

class SpaceShip {
public:
    SpaceShip();

    ~SpaceShip();

    void Draw();

    void MoveLeft();

    void MoveRight();

    void FireLaser();

private:
    Texture2D image{};
    Vector2 position{};


};
