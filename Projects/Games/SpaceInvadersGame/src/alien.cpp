//
// Created by rei on 5/15/25.
//

#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(const int type, const Vector2 position) {
    this->type = type;
    this->position = position;

    if (alienImages[type - 1].id == 0)

        switch (type) {
            case 1:
                alienImages[0] = LoadTexture("../Graphics/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("../Graphics/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("../Graphics/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("../Graphics/alien_1.png");
                break;
        }
}

void Alien::Draw() const {
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType() const {
    return type;
}

void Alien::UnloadImages() {
    for (const auto& texture : alienImages) {
        UnloadTexture(texture);
    }
}

Rectangle Alien::getRect() const {
    return {
        position.x, position.y,
        static_cast<float>(alienImages[type - 1].width),
        static_cast<float>(alienImages[type - 1].height)
    };
}

void Alien::Update(const int direction) {
    position.x += static_cast<float>(direction);
}
