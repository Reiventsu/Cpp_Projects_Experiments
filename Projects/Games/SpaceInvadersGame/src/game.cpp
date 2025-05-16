//
// Created by rei on 5/3/25.
//
#include "game.h"

#include <cstdlib>
#include <iomanip>

Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    mysteryShip.Spawn();
}

Game::~Game() {
    Alien::UnloadImages();
}

void Game::Update() {
    for (auto &laser: spaceShip.lasers) {
        laser.Update();
    }
    MoveAliens();
    AlienShootLaser();

    for (auto &laser: alienLasers) {
        laser.Update();
    }
    KillInactiveLasers();
    mysteryShip.Update();
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
    for (auto &laser: alienLasers) {
        laser.Draw();
    }
    mysteryShip.Draw();
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
    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it);
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
            MoveDownAliens(4);
        }
        if (alien.position.x < 0) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance) {
    for (auto &alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser() {
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({
                                        alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                        alien.position.y + alien.alienImages[alien.type - 1].height
                                    }, 6));
        timeLastAlienFired = GetTime();
    }
}
