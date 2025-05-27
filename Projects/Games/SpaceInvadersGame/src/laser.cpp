//
// Created by rei on 5/3/25.
//

#include "laser.h"

Laser::Laser(const Vector2 position, const int speed) {
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Draw() const {
    if (active)
        DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::getRect() const {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {
    position.y += static_cast<float>(speed);
    if (active) {
        if (static_cast<int>(position.y) > GetScreenHeight() -100 || position.y < 25) {
            active = false;
        }
    }
}
