//
// Created by rei on 5/15/25.
//

#pragma once
#include <raylib.h>


class Alien {
public:
    enum class Type {
        //Enum approach for alien type
        SMALL,      // 0
        MEDIUM,     // 1
        LARGE       // 2
    };

    Alien(Type type, Vector2 position);

    void update(int direction);

    void Draw() const;

    [[nodiscard]] Type getType() const;

    static void UnloadImages();

    static Texture2D alienImages[3];

    [[nodiscard]] Rectangle getRect() const;

    Type type;
    Vector2 position;
};
