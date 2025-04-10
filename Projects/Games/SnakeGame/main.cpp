//
// Created by rei on 4/9/25.
//

#include "pch.h"
#include "raylib.h"

Color green = Color(173, 204, 96, 255);
Color darkGreen = Color(43, 51, 24, 255);

int main() {
    std::cout << "Starting the game..." << std::endl;
    InitWindow(750, 750, "Snake Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
