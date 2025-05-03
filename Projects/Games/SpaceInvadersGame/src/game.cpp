//
// Created by rei on 5/3/25.
//
#include <iostream>
#include "game.h"

Game::Game() {
}

Game::~Game() {
}

void Game::Update() {
    for (auto &laser: spaceShip.lasers) {
        laser.Update();
    }
}

void Game::Draw() {
    spaceShip.Draw();

    for (auto &laser: spaceShip.lasers) {
        laser.Draw();
    }
    KillInactiveLasers();
}

void Game::ProcessInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceShip.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceShip.MoveRight();
    } else if (IsKeyDown(KEY_SPACE)) {
        spaceShip.FireLaser();
    }
}

void Game::KillInactiveLasers() {
    for (auto it = spaceShip.lasers.begin(); it != spaceShip.lasers.end();) {
        if (!it -> active) {
            it = spaceShip.lasers.erase(it);
        } else {
            ++ it;
        }
    }
}

