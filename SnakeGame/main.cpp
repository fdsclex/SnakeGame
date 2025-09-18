#include "interface.h"
#include "logic.h"
#include "highscores.h"
#include <vector>

using namespace std; // Добавлено для устранения ошибки с std::cout

int main() {
    const int width = 20, height = 20;
    std::vector<std::vector<char>> board(height, std::vector<char>(width, ' '));
    std::vector<Snake> snake = { {width / 2, height / 2} }; // Инициализация змеи
    int foodX, foodY;
    generateFood(board, foodX, foodY);
    char direction = 'd';
    int score = 0;
    std::string scoresFile = "Ресурсы/highscores.txt";

    while (true) {
        char input = getInput();
        if (input && (input == 'w' || input == 's' || input == 'a' || input == 'd')) direction = input;
        moveSnake(snake, direction);
        if (checkCollision(snake, width, height)) break;
        if (snake.front().x == foodX && snake.front().y == foodY) {
            score += 10;
            generateFood(board, foodX, foodY);
            snake.push_back(snake.back()); // Рост змеи при еде
        }
        // Обновление игрового поля
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                board[i][j] = ' ';
        for (const auto& s : snake) board[s.y][s.x] = '@';
        board[foodY][foodX] = '*';
        drawBoard(board);
    }
    saveScore(score, scoresFile);
    auto highscores = loadScores(scoresFile);
    cout << "Game Over! Score: " << score << "\nHigh Scores: ";
    for (int s : highscores) cout << s << " ";
    return 0;
}