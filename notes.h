#pragma once
#include <vector>
#include <iostream>
using namespace std;


class Notes {
private:
    vector<vector<vector<int>>> notes = vector<vector<vector<int>>>(10, vector<vector<int>>(10, vector<int>(10, 0)));

public:

    // Функция для добавления заметки для определенной ячейки судоку
    void addNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = number;
        }
        else {
            std::cout << "Некорректная строка, столбец или число!" << std::endl;
        }
    }

    // Функция для удаления заметки для определенной ячейки судоку
    void deleteNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = 0;
        }
        else {
            std::cout << "Некорректная строка, столбец или число!" << std::endl;
        }
    }

    // Функция для вывода всех заметок для определенной ячейки судоку
    void printNotes(int row, int col) {
        if (isValidCell(row, col)) {
            std::cout << "Заметки для клетки (" << row << ", " << col << "): ";
            for (int num : notes[row][col]) {
                if (num != 0) {
                    std::cout << num << "; ";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Некорректная строка или столбец!" << std::endl;
        }
    }

private:
    // Проверка валидности номера
    bool isValidNumber(int number) {
        return number >= 1 && number <= 9;
    }

    // Проверка валидности ячейки
    bool isValidCell(int row, int col) {
        return row >= 1 && row <= 9 && col >= 1 && col <= 9;
    }
};
