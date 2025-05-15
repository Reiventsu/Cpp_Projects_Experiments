//
// Created by rei on 5/15/25.
//

#pragma once
#include <vector>
#include "block.h"

class Obstacle {
public:
    Obstacle(Vector2 position);

    void Draw();

    Vector2 position;
    std::vector<Block> blocks;
    std::vector<std::vector<int> > grid;

private:
};
