#include "interface.h"
#include "logic.h"
#include "highscores.h"
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iomanip> // Для форматирования вывода
#include <iostream>
using namespace std;

int main() {
    const int width = 20, height = 20;
    std::vector<std::vector<char>> board(height, std::vector<char>(width, '#')); // Границы '#'
    for (int i = 1; i < height - 1; ++i)
        for (int j = 1; j < width - 1; ++j)
            board[i][j] = ' '; // Поле внутри границ

    // Инициализация змеи
    std::vector<Snake> snake = { {width / 2, height / 2} };
    board[height / 2][width / 2] = '@'; // Отображаем змею на старте

    int foodX, foodY;
    generateFood(board, foodX, foodY); // Генерируем еду и обновляем board

    char direction = 'd'; // Начальное направление вправо
    int score = 0;
    std::string scoresFile = "highscores.txt";
    const int delayMs = 200; // Задержка 0.2 секунды

    setConsoleSize(40, height + 5); // Увеличиваем высоту для таблицы

    auto lastUpdate = chrono::steady_clock::now();
    while (true) {
        char input = getInput();
        if (input && (input == 'w' || input == 'a' || input == 's' || input == 'd')) {
            if ((direction == 'd' && input != 'a') || (direction == 'a' && input != 'd') || (direction == 'w' && input != 's') || (direction == 's' && input != 'w')) {
                direction = input; // Обновляем только если не противоположное
            }
        }

        auto currentTime = chrono::steady_clock::now();
        chrono::duration<double, milli> elapsed = currentTime - lastUpdate;
        if (elapsed.count() >= delayMs) {
            // Очищаем поле перед обновлением
            for (int i = 1; i < height - 1; ++i)
                for (int j = 1; j < width - 1; ++j)
                    board[i][j] = ' ';

            moveSnake(snake, direction, width, height);
            if (checkCollision(snake, width, height)) break;

            // Обновляем всё тело змеи на board
            for (const auto& segment : snake) {
                if (segment.x > 0 && segment.x < width - 1 && segment.y > 0 && segment.y < height - 1) {
                    board[segment.y][segment.x] = '@';
                }
            }

            // Обновляем позицию еды на board
            board[foodY][foodX] = '*';

            if (snake.front().x == foodX && snake.front().y == foodY) {
                score += 10;
                generateFood(board, foodX, foodY); // Генерируем новую еду
                snake.push_back(snake.back()); // Рост змеи
            }

            drawBoard(board); // Отрисовка обновлённого поля
            lastUpdate = currentTime;
        }
    }

    saveScore(score, scoresFile);
    auto highscores = loadScores(scoresFile);
    cout << "\n+-----------------+" << endl;
    cout << "|   Game Over!    |" << endl;
    cout << "+-----------------+" << endl;
    cout << "| Score: " << setw(10) << score << " |" << endl;
    cout << "+-----------------+" << endl;
    cout << "| High Scores     |" << endl;
    cout << "+-----------------+" << endl;
    for (size_t i = 0; i < highscores.size(); ++i) {
        cout << "| " << setw(2) << (i + 1) << ". " << setw(10) << highscores[i] << " |" << endl;
    }
    cout << "+-----------------+" << endl;
    return 0;
}