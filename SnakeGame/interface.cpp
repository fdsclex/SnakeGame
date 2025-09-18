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

char getInput() {
    if (_kbhit()) return _getch(); // ���������������� ����, ������ �������� � <conio.h>
    return ' '; // �����������
}