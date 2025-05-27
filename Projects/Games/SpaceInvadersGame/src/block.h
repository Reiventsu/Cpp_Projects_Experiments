//
// Created by rei on 5/15/25.
//

#pragma once
#include <raylib.h>


class Block {
public:
    explicit Block(Vector2 position);

    void Draw() const;

    [[nodiscard]] Rectangle getRect() const;

private:
    Vector2 position{};
};
