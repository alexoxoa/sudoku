#pragma once
#include <vector>
#include <iostream>
using namespace std;


class Notes {
private:
    vector<vector<vector<int>>> notes = vector<vector<vector<int>>>(10, vector<vector<int>>(10, vector<int>(10, 0)));

public:

    // ������� ��� ���������� ������� ��� ������������ ������ ������
    void addNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = number;
        }
        else {
            std::cout << "������������ ������, ������� ��� �����!" << std::endl;
        }
    }

    // ������� ��� �������� ������� ��� ������������ ������ ������
    void deleteNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = 0;
        }
        else {
            std::cout << "������������ ������, ������� ��� �����!" << std::endl;
        }
    }

    // ������� ��� ������ ���� ������� ��� ������������ ������ ������
    void printNotes(int row, int col) {
        if (isValidCell(row, col)) {
            std::cout << "������� ��� ������ (" << row << ", " << col << "): ";
            for (int num : notes[row][col]) {
                if (num != 0) {
                    std::cout << num << "; ";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "������������ ������ ��� �������!" << std::endl;
        }
    }

private:
    // �������� ���������� ������
    bool isValidNumber(int number) {
        return number >= 1 && number <= 9;
    }

    // �������� ���������� ������
    bool isValidCell(int row, int col) {
        return row >= 1 && row <= 9 && col >= 1 && col <= 9;
    }
};
