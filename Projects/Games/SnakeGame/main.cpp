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
int offset = 75;

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
    Vector2 direction{};
    Vector2 nextDirection{};
    bool shouldGrow = false;

    void ProcessInput(const Vector2 newDirection) {
        if (newDirection.x == -direction.x && newDirection.y == -direction.y) return;

        if ((newDirection.x == 0 || direction.x == 0) &&
            (newDirection.y == 0 || direction.y == 0)) {
            nextDirection = newDirection;
        }
    }

    void UpdateSnake() {
        if (nextDirection.x != 0 || nextDirection.y != 0) {
            direction = nextDirection;
            nextDirection = {0, 0};
        }

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
                static_cast<float>(offset) + x * static_cast<float>(cellSize),
                static_cast<float>(offset) + y * static_cast<float>(cellSize),
                static_cast<float>(cellSize),
                static_cast<float>(cellSize)
            };
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Reset() {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
        nextDirection = {0, 0};
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
            offset + static_cast<int>(position.x) * cellSize,
            offset + static_cast<int>(position.y) * cellSize,
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
    bool gameRunning = true;
    int gameScore = 0;

    SnakeGame() : food(snake.body) {
        snake.Reset();
    }

    void CheckCollisionWithFood() {
        if (Vector2Equals(snake.body.front(), food.position)) {
            std::cout << "Eating Food" << std::endl;
            food.position = Food::GenerateRandomPos(snake.body);
            snake.shouldGrow = true;
            gameScore++;
        }
    }

    void Update() {
        if (gameRunning) {
            snake.UpdateSnake();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void Draw() const {
        food.drawFood();
        snake.drawSnake();
    }

    void CheckCollisionWithEdges() {
        if (snake.body.front().x == static_cast<float>(cellCount) || snake.body.front().x == -1) {
            GameOver();
        }
        if (snake.body.front().y == static_cast<float>(cellCount) || snake.body.front().y == -1) {
            GameOver();
        }
    }

    void CheckCollisionWithTail() {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body.front(), headlessBody)) {
            GameOver();
        }
    }

    void GameOver() {
        std::cout << "GAME OVER" << std::endl;
        snake.Reset();
        food.position = Food::GenerateRandomPos(snake.body);
        gameRunning = false;
    }
};

// main function of the program makes the window and handles input that interact with the other parts of the program.
int main() {
    std::cout << "Starting the game..." << std::endl;
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);
    float accumulatedTime = 0.0f;

    auto game = SnakeGame();

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (IsKeyPressed(KEY_UP)) game.snake.ProcessInput({0, -1});
        if (IsKeyPressed(KEY_DOWN)) game.snake.ProcessInput({0, 1});
        if (IsKeyPressed(KEY_LEFT)) game.snake.ProcessInput({-1, 0});
        if (IsKeyPressed(KEY_RIGHT)) game.snake.ProcessInput({1, 0});

        if (!game.gameRunning && IsKeyPressed(KEY_SPACE)) {
            game.gameRunning = true;
            game.snake.Reset();
            game.gameScore = 0;
        }

        constexpr float moveInterval = 0.2f;
        const float deltaTime = GetFrameTime();
        accumulatedTime += deltaTime;

        float speedMultiplier;
        if (IsKeyDown(KEY_SPACE)) {
            speedMultiplier = 2.0f;
        } else {
            speedMultiplier = 1.0f;
        }
        const float effectiveInterval = moveInterval / speedMultiplier;

        while (accumulatedTime >= effectiveInterval) {
            game.Update();
            accumulatedTime -= effectiveInterval;
        }

        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{
                                 static_cast<float>(offset) - 5,
                                 static_cast<float>(offset) - 5,
                                 static_cast<float>(cellSize * cellCount + 10),
                                 static_cast<float>(cellSize * cellCount + 10)
                             },
                             5, darkGreen);

        DrawText(TextFormat("%i", game.gameScore), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        if (!game.gameRunning) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));

            DrawText("GAME OVER!",
                     offset + cellSize * cellCount / 2 - MeasureText("GAME OVER!", 70) / 2,
                     offset + cellSize * cellCount / 2 - 120,
                     70, green);

            const char *scoreText = TextFormat("your score was: %i", game.gameScore);
            DrawText(scoreText,
                     offset + cellSize * cellCount / 2 - MeasureText(scoreText, 40) / 2,
                     offset + cellSize * cellCount / 2 - 40,
                     40, green);

            DrawText("Press SPACE to restart or ESC to close",
                     offset + cellSize * cellCount / 2 - MeasureText("Press SPACE to Restart or ESC to close", 30) / 2,
                     offset + cellSize * cellCount / 2 + 20,
                     30, green);
        }
        EndDrawing();
    }

    CloseWindow();

    return
            0;
}
