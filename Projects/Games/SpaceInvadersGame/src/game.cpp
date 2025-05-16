//
// Created by rei on 5/3/25.
//
#include "game.h"

Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
}

Game::~Game() {
    Alien::UnloadImages();
}

void Game::Update() {
    for (auto &laser: spaceShip.lasers) {
        laser.Update();
    }
    MoveAliens();
    KillInactiveLasers();
}

void Game::Draw() {
    spaceShip.Draw();

    for (auto &laser: spaceShip.lasers) {
        laser.Draw();
    }

    for (auto &obstacle: obstacles) {
        obstacle.Draw();
    }

    for (auto &alien: aliens) {
        alien.Draw();
    }
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
        if (!it->active) {
            it = spaceShip.lasers.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 11; col++) {
            int alienType;
            if (row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + col * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto &alien: aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()) {
            aliensDirection = -1;
        }
        if (alien.position.x < 0) {
            aliensDirection = 1;
        }

        alien.Update(aliensDirection);
    }
}
