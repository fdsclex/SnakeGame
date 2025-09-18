#pragma once
#include <vector>

struct Snake { int x, y; };

void moveSnake(std::vector<Snake>& snake, char direction);
bool checkCollision(const std::vector<Snake>& snake, int width, int height);
void generateFood(std::vector<std::vector<char>>& board, int& foodX, int& foodY);