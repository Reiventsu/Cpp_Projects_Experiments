//
// Created by rei on 5/3/25.
//

#include "spaceship.h"

SpaceShip::SpaceShip() {
    image = LoadTexture("../Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::Draw() {
    DrawTextureV(image, position, WHITE);
}

void SpaceShip::MoveLeft() {
    position.x -= 7;
    if (position.x < 0) { position.x = 0; }
}

void SpaceShip::MoveRight() {
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}
