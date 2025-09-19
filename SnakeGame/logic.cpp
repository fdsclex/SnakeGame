#include "logic.h"
#include <cstdlib>
#include <ctime>

void moveSnake(std::vector<Snake>& snake, char direction, int width, int height) {
    if (snake.empty()) return;
    Snake head = snake.front();
    Snake newHead = head; // Создаём новую голову для обновления
    if (direction == 'w' && head.y > 1) newHead.y--;
    else if (direction == 's' && head.y < height - 2) newHead.y++;
    else if (direction == 'a' && head.x > 1) newHead.x--;
    else if (direction == 'd' && head.x < width - 2) newHead.x++;
    snake.insert(snake.begin(), newHead); // Добавляем новую голову
    snake.pop_back(); // Удаляем последний сегмент (хвост)
}

bool checkCollision(const std::vector<Snake>& snake, int width, int height) {
    if (snake.empty()) return true;
    Snake head = snake.front();
    if (head.x <= 0 || head.x >= width - 1 || head.y <= 0 || head.y >= height - 1) return true; // Столкновение с границами
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head.x == snake[i].x && head.y == snake[i].y) return true; // Самопересечение
    }
    return false;
}

void generateFood(std::vector<std::vector<char>>& board, int& foodX, int& foodY) {
    srand(static_cast<unsigned>(time(0)));
    do {
        foodX = rand() % (board[0].size() - 2) + 1; // Еда внутри границ
        foodY = rand() % (board.size() - 2) + 1;
    } while (board[foodY][foodX] != ' ');
    board[foodY][foodX] = '*'; // Устанавливаем еду на поле
}