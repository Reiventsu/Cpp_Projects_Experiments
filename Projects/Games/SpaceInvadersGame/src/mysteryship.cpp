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
    int side = GetRandomValue(0, 1);
    if (side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    IsAlive = true;
}

void MysteryShip::Update() {
    if (IsAlive) {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width -25 || position.x < 25) {
            IsAlive = false;
        }
    }
}

void MysteryShip::Draw() {
    if (IsAlive) {
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle MysteryShip::getRect() {
    if (IsAlive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}
