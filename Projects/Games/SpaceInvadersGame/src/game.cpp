//
// Created by rei on 5/3/25.
//

#include "game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::Draw() {
    spaceShip.Draw();
}

void Game::ProcessInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceShip.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceShip.MoveRight();
    }
}
