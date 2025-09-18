#include "logic.h"
#include <cstdlib>
#include <ctime>

void moveSnake(std::vector<Snake>& snake, char direction) {
    if (snake.empty()) return; // Проверка на пустой вектор
    Snake head = snake.front();
    if (direction == 'w') head.y--;
    else if (direction == 's') head.y++;
    else if (direction == 'a') head.x--;
    else if (direction == 'd') head.x++;
    snake.insert(snake.begin(), head);
    snake.pop_back(); // Убираем хвост (рост обрабатывается отдельно)
}

bool checkCollision(const std::vector<Snake>& snake, int width, int height) {
    if (snake.empty()) return true; // Проверка на пустой вектор
    Snake head = snake.front();
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) return true;
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head.x == snake[i].x && head.y == snake[i].y) return true;
    }
    return false;
}

void generateFood(std::vector<std::vector<char>>& board, int& foodX, int& foodY) {
    srand(static_cast<unsigned>(time(0)));
    do {
        foodX = rand() % board[0].size();
        foodY = rand() % board.size();
    } while (board[foodY][foodX] != ' ');
    board[foodY][foodX] = '*';
}