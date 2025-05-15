//
// Created by rei on 4/16/25.
//
#include "pch.h"

// Global values
Color grey = {29, 29, 27, 255};
constexpr int windowWidth = 750;
constexpr int windowHeight = 700;

int main() {
    InitWindow(windowWidth, windowHeight, "SpaceInvadersGame");
    SetTargetFPS(60);

    Game game;
    Obstacle obstacle = Obstacle({100, 100});

    while (!WindowShouldClose()) {

        game.ProcessInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        obstacle.Draw();

        EndDrawing();
    }

    CloseWindow();
}
