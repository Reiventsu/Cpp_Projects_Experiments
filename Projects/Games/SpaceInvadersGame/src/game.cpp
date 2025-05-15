//
// Created by rei on 5/3/25.
//
#include "game.h"

Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
}

Game::~Game() {
}

void Game::Update() {
    for (auto &laser: spaceShip.lasers) {
        laser.Update();
    }
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
            float x = col * 55;
            float y = row * 55;
            aliens.push_back(Alien(1, {x, y}));
        }
    }
    return aliens;
}