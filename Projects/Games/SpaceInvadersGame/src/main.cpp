//
// Created by rei on 4/16/25.
//
#include <raylib.h>
#include "game.h"
#include <string>


// Template function for score
std::string FormatWithLeadingZeros(const int number, const int width) {
    const std::string numberText = std::to_string(number);
    const int leadingZeros = std::max(width - static_cast<int>(numberText.length()), 0);
    return std::string(leadingZeros, '0') + numberText;
}

// Global values
constexpr Color grey = {29, 29, 27, 255};
constexpr Color yellow = {243, 216, 63, 255};
constexpr int offset = 50;
constexpr int windowWidth = 750;
constexpr int windowHeight = 700;

int main() {
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "SpaceInvadersGame");
    const Font font = LoadFontEx("../Fonts/monogram.ttf", 64, nullptr, 0);
    const Texture2D spaceshipImage = LoadTexture("../Graphics/spaceship.png");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.ProcessInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if (game.IsGameRunning) {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        // Shows the lives the player has left
        float x = 50.0;
        for (int i = 0; i < game.playerLives; i++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50.0;
        }

        // Handling score
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.playerScore, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        // Handling highscore
        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highScoreText = FormatWithLeadingZeros(game.playerHighScore, 5);
        DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);


        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}
