#include "interface.h"
#include <iostream>
#include <windows.h> // Для system("cls")
#include <conio.h>   // Для _kbhit() и _getch() (добавлено для исправления ошибки)

void drawBoard(const std::vector<std::vector<char>>& board) {
    system("cls"); // Очистка экрана для Windows
    for (const auto& row : board) {
        for (char cell : row) std::cout << cell << ' ';
        std::cout << std::endl;
    }
}
void setConsoleSize(int width, int height) {
    char cmd[50];
    sprintf_s(cmd, "mode con: cols=%d lines=%d", width, height);
    system(cmd);
}                                                                                                                                                                                                                   
char getInput() {                                                               
    if (_kbhit()) return _getch(); // Неконтролируемый ввод, теперь работает с <conio.h>        
    return ' '; // Плейсхолдер
}