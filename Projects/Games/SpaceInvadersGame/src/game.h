//
// Created by rei on 5/3/25.
//

#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"

class Game {
public:
    Game();

    ~Game();

    void Draw();

    void Update();

    void ProcessInput();

    bool IsGameRunning;
    int playerLives;

private:
    void KillInactiveLasers();

    std::vector<Obstacle> CreateObstacles();

    std::vector<Alien> CreateAliens();

    SpaceShip spaceShip;

    void MoveAliens();

    void MoveDownAliens(int distance);

    void AlienShootLaser();

    void CheckForCollision();

    void GameOver();
    void ResetGame();
    void InitGame();

    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection;
    std::vector<Laser> alienLasers;
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;
    MysteryShip mysteryShip;
    float mysteryShipSpawnInterval;
    float mysteryShipTimeLastSpawn;
};
