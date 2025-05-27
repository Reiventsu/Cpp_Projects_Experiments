//
// Created by rei on 5/15/25.
//

#include "block.h"

Block::Block(const Vector2 position) {
    this->position = position;
}

void Block::Draw() const {
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), 3, 3, {243, 216, 63, 255});
}

Rectangle Block::getRect() const {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
    return rect;
}
