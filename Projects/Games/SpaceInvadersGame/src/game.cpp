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
        double currentTime = GetTime();
        if (currentTime - mysteryShipTimeLastSpawn > mysteryShipSpawnInterval) {
            mysteryShip.Spawn();
            mysteryShipTimeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
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
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
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
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25) {
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
    mysteryShipSpawnInterval = GetRand omValue(10, 20);
}

void Game::CheckForHighScore() {
    if (playerScore > playerHighScore) {
        playerHighScore = playerScore;
        SaveHighScore(playerHighScore);
    }
}

void Game::SaveHighScore(int playerHighScore) {
    std::ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile << playerHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "Unable to save highscore to file" << std::endl;
    }
}

int Game::LoadHighScore() {
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "Unable to load highscore from file" << std::endl;
    }
    return loadedHighScore;
}
