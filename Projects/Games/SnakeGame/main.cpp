// Created by rei on 4/9/25.

//This project is written in CLion, and so I use its Clang-Tidy and I do follow it pretty blindly and try to resolve every suggestion it has
// unless it breaks something, and I'm doing this because I'm making the assumption it'll teach me something
// about best-practices as well as maintainable, well-structured code.

#include "pch.h"

// Global values
auto green = Color(173, 204, 96, 255);
auto darkGreen = Color(43, 51, 24, 255);

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool ElementInDeque(const Vector2 element, const std::deque<Vector2> &deque) {
    return std::ranges::any_of(deque, [&element](const Vector2 &i) {
        return Vector2Equals(i, element);
    });
};

bool eventTriggered(const double interval) {
    if (const double currentTime = GetTime(); currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Le snek
class Snake {
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool shouldGrow = false;

    void UpdateSnake() {
        const Vector2 newHead = Vector2Add(body.front(), direction);
        body.push_front(newHead);
        if (!shouldGrow) {
            body.pop_back();
        }
        shouldGrow = false;
    }

    void drawSnake() const {
        for (const auto &[x, y]: body) {
            const auto segment = Rectangle{
                x * static_cast<float>(cellSize),
                y * static_cast<float>(cellSize),
                static_cast<float>(cellSize),
                static_cast<float>(cellSize)
            };
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
};

// Class for food for the snake to eat
class Food {
public:
    Vector2 position{};
    Texture2D texture{};

    explicit Food(const std::deque<Vector2> &snakeBody) {
        const Image image = LoadImage("../Graphics/FoodImage.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void drawFood() const {
        DrawTexture(
            texture,
            static_cast<int>(position.x) * cellSize,
            static_cast<int>(position.y) * cellSize,
            WHITE
        );
    }

    static Vector2 GenerateRandomCell() {
        const int x = GetRandomValue(0, cellCount - 1);
        const int y = GetRandomValue(0, cellCount - 1);
        return Vector2{
            static_cast<float>(x),
            static_cast<float>(y)
        };
    }

    static Vector2 GenerateRandomPos(const std::deque<Vector2> &snakeBody) {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody)) {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class SnakeGame {
public:
    Snake snake;
    Food food;

    SnakeGame() : food(snake.body) {}

    void CheckCollisionWithFood() {
        if (Vector2Equals(snake.body.front(), food.position)) {
            std::cout << "Eating Food" << std::endl;
            food.position = Food::GenerateRandomPos(snake.body);
            snake.shouldGrow = true;
        }
    }

    void Update() {
        snake.UpdateSnake();
        CheckCollisionWithFood();
    }

    void Draw() const {
        food.drawFood();
        snake.drawSnake();
    }
};

int main() {
    std::cout << "Starting the game..." << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    auto game = SnakeGame();

    while (WindowShouldClose() == false) {
        BeginDrawing();

        if (eventTriggered(0.2)) {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
        }

        ClearBackground(green);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
