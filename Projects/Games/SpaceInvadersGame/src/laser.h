//
// Created by rei on 5/3/25.
//
#pragma once
#include <raylib.h>

class Laser {
public:
    Laser(Vector2 position, int speed);

    void Update();

    void Draw();

    bool active;

private:
    Vector2 position;
    int speed;
};
