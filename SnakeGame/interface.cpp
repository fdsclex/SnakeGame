#include "interface.h"
#include <iostream>
#include <windows.h> // ��� system("cls")
#include <conio.h>   // ��� _kbhit() � _getch() (��������� ��� ����������� ������)

void drawBoard(const std::vector<std::vector<char>>& board) {
    system("cls"); // ������� ������ ��� Windows
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
    if (_kbhit()) return _getch(); // ���������������� ����, ������ �������� � <conio.h>        
    return ' '; // �����������
}