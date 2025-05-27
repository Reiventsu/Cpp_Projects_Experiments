//
// Created by rei on 5/3/25.
//

#include "spaceship.h"

SpaceShip::SpaceShip() {
    image = LoadTexture("../Graphics/spaceship.png");
    position.x = static_cast<float>(GetScreenWidth() - image.width) / 2;
    position.y = static_cast<float>(GetScreenHeight()) - static_cast<float>(image.height) - 100;
    lastFireTime = 0.0;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::Draw() const {
    DrawTextureV(image, position, WHITE);
}

void SpaceShip::MoveLeft() {
    position.x -= 7;
    if (position.x < 25) { position.x = 25; }
}

void SpaceShip::MoveRight() {
    position.x += 7;
    if (position.x > static_cast<float>(GetScreenWidth()) - static_cast<float>(image.width) - 25) {
        position.x = static_cast<float>(GetScreenWidth()) - static_cast<float>(image.width) - 25;
    }
}

void SpaceShip::FireLaser() {
    if (GetTime() - lastFireTime >= 0.35) {
        lasers.push_back(Laser({position.x + static_cast<float>(image.width) / 2 - 2, position.y}, -6));
        lastFireTime = GetTime();
    }
}


void SpaceShip::ResetPlayerShip() {
    position.x = static_cast<float>(GetScreenWidth() - image.width)/ 2.0f;
    position.y = static_cast<float>(GetScreenWidth()) - static_cast<float>(image.height) - 100;
    lasers.clear();
}

Rectangle SpaceShip::getRect() const {
    return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}
