//
// Created by rei on 5/16/25.
//

#pragma once
#include <raylib.h>


class MysteryShip {
public:
    MysteryShip();
    ~MysteryShip();
    void Update();
    void Draw();
    Rectangle getRect();
    void Spawn();
    bool IsAlive;
private:
    Vector2 position;
    Texture2D image;
    int speed;
};
