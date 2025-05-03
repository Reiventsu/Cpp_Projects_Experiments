//
// Created by rei on 4/16/25.
//
#include "pch.h"
#include "spaceship.h"

// Global values
Color grey = {29, 29, 27, 255};
constexpr int windowWidth = 750;
constexpr int windowHeight = 700;

int main() {

    InitWindow(windowWidth, windowHeight, "SpaceInvadersGame");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(grey);

        EndDrawing();
    }

    CloseWindow();
}
