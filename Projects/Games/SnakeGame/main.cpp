//
// Created by rei on 4/9/25.
//

#include "pch.h"
#include "raylib.h"

Color green = Color(173, 204, 96, 255);
Color darkGreen = Color(43, 51, 24, 255);

int cellSize = 30;
int cellCount = 25;

class Food {
public:
    Vector2 position = {5, 6};
    Texture2D texture;

    Food() {
        Image image = LoadImage("../Graphics/FoodImage.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void drawFood() {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }
};

int main() {
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    Food food = Food();

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(green);
        food.drawFood();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
