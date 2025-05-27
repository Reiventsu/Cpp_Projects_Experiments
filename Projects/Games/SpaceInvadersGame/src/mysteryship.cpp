//
// Created by rei on 5/16/25.
//

#include "mysteryship.h"

MysteryShip::MysteryShip() {
    image = LoadTexture("../Graphics/mystery.png");
    IsAlive = false;
}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

void MysteryShip::Spawn() {
    position.y = 90;
    if (const int side = GetRandomValue(0, 1); side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = static_cast<float>(GetScreenWidth()) - static_cast<float>(image.width) - 25;
        speed = -3;
    }
    IsAlive = true;
}

void MysteryShip::Update() {
    if (IsAlive) {
        position.x += static_cast<float>(speed);
        if (static_cast<int>(position.x) > GetScreenWidth() - image.width -25 || position.x < 25) {
            IsAlive = false;
        }
    }
}

void MysteryShip::Draw() const {
    if (IsAlive) {
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle MysteryShip::getRect() const {
    if (IsAlive) {
        return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
    }
    return {position.x, position.y, 0, 0};
}
