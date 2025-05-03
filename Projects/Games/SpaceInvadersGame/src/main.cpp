//
// Created by rei on 4/16/25.
//
#include "pch.h"

int main() {
    constexpr int windowWidth = 750;
    constexpr int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "SpaceInvadersGame");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
}
