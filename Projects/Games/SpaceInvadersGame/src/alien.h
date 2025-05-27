//
// Created by rei on 5/15/25.
//

#pragma once
#include <raylib.h>


class Alien {
public:
    Alien(int type, Vector2 position);
    void Update(int direction);
    void Draw() const;
    [[nodiscard]] int GetType() const;
    static void UnloadImages();
    static Texture2D alienImages[3];
    int type;
    Vector2 position{};
    [[nodiscard]] Rectangle getRect() const;

};
