//
// Created by rei on 4/16/25.
//
#include <raylib.h>
#include "game.h"
#include <string>

// Global values
constexpr Color grey = {29, 29, 27, 255};
constexpr Color yellow = {243, 216, 63, 255};
constexpr int offset = 50;
constexpr int windowWidth = 750;
constexpr int windowHeight = 700;

int main() {
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "SpaceInvadersGame");
    Font font = LoadFontEx("../Fonts/monogram.ttf", 64, 0, 0);
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.ProcessInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
