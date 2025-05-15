//
// Created by rei on 5/15/25.
//

#pragma once
#include <raylib.h>


class Alien {
public:
    Alien(int type, Vector2 position);
    void Update();
    void Draw();
    int GetType();
    Texture2D image;
    int type;
    Vector2 position;

private:
};
