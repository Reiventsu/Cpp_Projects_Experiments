//
// Created by rei on 5/3/25.
//

#include "spaceship.h"

SpaceShip::SpaceShip() {
    image = LoadTexture("../Graphics/spaceship.png");
    position.x = 100;
    position.y = 100;
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
}

void SpaceShip::Draw() {
    DrawTextureV(image, position, WHITE);
}
