//
// Created by rei on 5/3/25.
//
#include "game.h"
#include <iostream>
#include <fstream>

Game::Game() {
    InitGame();
}

Game::~Game() {
    Alien::UnloadImages();
}

void Game::Update() {
    if (IsGameRunning) {
        if (const auto currentTime = GetTime(); currentTime - mysteryShipTimeLastSpawn > mysteryShipSpawnInterval) {
            mysteryShip.Spawn();
            mysteryShipTimeLastSpawn = static_cast<float>(GetTime());
            mysteryShipSpawnInterval = static_cast<float>(GetRandomValue(10, 20));
        }

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
        CheckForCollision();
    } else {
        if (IsKeyDown(KEY_ENTER)) {
            ResetGame();
            InitGame();
        }
    }
}

void Game::Draw() const {
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
    if (IsGameRunning) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceShip.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceShip.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceShip.FireLaser();
        }
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
    const float obstacleWidth = static_cast<float>(Obstacle::grid[0].size()) * 3;
    const float gap = (static_cast<float>(GetScreenWidth()) - 4 * obstacleWidth) / 5;

    for (int i = 0; i < 4; i++) {
        const float offsetX =
                (static_cast<float>(i) + 1.0f) * gap +
                static_cast<float>(i) * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, static_cast<float>(GetScreenHeight() - 200)}));
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

            const float x = static_cast<float>(75) + static_cast<float>(col) * 55;
            const float y = static_cast<float>(110) + static_cast<float>(row) * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto &alien: aliens) {
        const auto alienWidth = static_cast<float>(Alien::alienImages[alien.type - 1].width);

        if (const auto screenWidth = static_cast<float>(GetScreenWidth()); alien.position.x + alienWidth > screenWidth - 25.0f) {
            aliensDirection = -1;
            MoveDownAliens();
        }
        if (alien.position.x < 25.0f) {
            aliensDirection = 1;
            MoveDownAliens();
        }

        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens() {
    for (auto &alien: aliens) {
        alien.position.y += 4;
    }
}

void Game::AlienShootLaser() {
    if (const double currentTime = GetTime(); currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        const auto randomIndex = GetRandomValue(0, static_cast<int>(aliens.size()) - 1);
        const Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({
                                        alien.position.x + static_cast<float>(Alien::alienImages[alien.type - 1].width) / 2,
                                        alien.position.y + static_cast<float>(Alien::alienImages[alien.type - 1].height)
                                    }, 6));
        timeLastAlienFired = static_cast<float>(GetTime());
    }
}

void Game::CheckForCollision() {
    // Spaceship Lasers
    for (auto &laser: spaceShip.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                if (it->type == 1) {
                    playerScore += 100;
                } else if (it->type == 2) {
                    playerScore += 200;
                } else if (it->type == 3) {
                    playerScore += 300;
                }
                CheckForHighScore();

                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for (auto &obstacle: obstacles) {
            auto obstacle_it = obstacle.blocks.begin();
            while (obstacle_it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(obstacle_it->getRect(), laser.getRect())) {
                    obstacle_it = obstacle.blocks.erase(obstacle_it);
                    laser.active = false;
                } else {
                    ++obstacle_it;
                }
            }
        }
        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect())) {
            mysteryShip.IsAlive = false;
            laser.active = false;
            playerScore += 500;
            CheckForHighScore();
        }
    }

    // Alien Lasers
    for (auto &laser: alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceShip.getRect())) {
            laser.active = false;
            playerLives--;
            if (playerLives == 0) {
                GameOver();
            }
        }
        for (auto &obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }
    // Alien Collision with obstacles

    for (auto &alien: aliens) {
        for (auto &obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceShip.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver() {
    IsGameRunning = false;
}

void Game::ResetGame() {
    spaceShip.ResetPlayerShip();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::InitGame() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    mysteryShipTimeLastSpawn = 0;
    playerLives = 3;
    playerScore = 0;
    playerHighScore = LoadHighScore();
    IsGameRunning = true;
    mysteryShipSpawnInterval = static_cast<float>(GetRandomValue(10, 20));
}

void Game::CheckForHighScore() {
    if (playerScore > playerHighScore) {
        playerHighScore = playerScore;
        SaveHighScore(playerHighScore);
    }
}

void Game::SaveHighScore(const int playerHighScore) {
    if (std::ofstream highScoreFile("highscore.txt"); highScoreFile.is_open()) {
        highScoreFile << playerHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "Unable to save highscore to file" << std::endl;
    }
}

int Game::LoadHighScore() {
    int loadedHighScore = 0;
    if (std::ifstream highScoreFile("highscore.txt"); highScoreFile.is_open()) {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "Unable to load highscore from file" << std::endl;
    }
    return loadedHighScore;
}
