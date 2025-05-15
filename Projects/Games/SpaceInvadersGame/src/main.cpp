//
// Created by rei on 4/16/25.
//
#include <raylib.h>
#include "game.h"
#include <string>

// Global values
Color grey = {29, 29, 27, 255};
constexpr int windowWidth = 750;
constexpr int windowHeight = 700;

int main() {
    InitWindow(windowWidth, windowHeight, "SpaceInvadersGame");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {

        game.ProcessInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
