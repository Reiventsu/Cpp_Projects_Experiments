//
// Created by rei on 5/15/25.
//

#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(Type type, const Vector2 position)
    : type(type), position(position) {
    const int textureIndex = static_cast<int>(type);
    if (alienImages[textureIndex].id == 0)

        switch (type) {
            case Type::SMALL:
                alienImages[0] = LoadTexture("../Graphics/alien_1.png");
                break;
            case Type::MEDIUM:
                alienImages[1] = LoadTexture("../Graphics/alien_2.png");
                break;
            case Type::LARGE:
                alienImages[2] = LoadTexture("../Graphics/alien_3.png");
                break;
        }
}

void Alien::Draw() const {
    const int textureIndex = static_cast<int>(type);
    DrawTextureV(alienImages[textureIndex], position, WHITE);
}

Alien::Type Alien::getType() const {
    return type;
}

void Alien::UnloadImages() {
    for (auto &texture: alienImages) {
        if (texture.id != 0)
            UnloadTexture(texture);
        texture = {};
    }
}

Rectangle Alien::getRect() const {
    const int textureIndex = static_cast<int>(type);
    return {
        position.x, position.y,
        static_cast<float>(alienImages[textureIndex].width),
        static_cast<float>(alienImages[textureIndex].height)
    };
}

void Alien::update(const int direction) {
    position.x += static_cast<float>(direction);
}
