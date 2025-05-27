//
// Created by rei on 5/15/25.
//

#pragma once
#include <vector>
#include "block.h"

class Obstacle {
public:
    explicit Obstacle(Vector2 position);

    void Draw() const;

    Vector2 position{};
    std::vector<Block> blocks;
    static std::vector<std::vector<int> > grid;

};
