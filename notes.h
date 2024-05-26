#pragma once
#include <vector>
#include <iostream>
using namespace std;


class Notes {
private:
    vector<vector<vector<int>>> notes = vector<vector<vector<int>>>(10, vector<vector<int>>(10, vector<int>(10, 0)));

public:

    //���������t ������� ��� ������������ ������ ������
    void addNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = number;
        }
        else {
            cout << "������������ ����" << endl;
        }
    }

    //�������� ������� ��� ������������ ������ ������
    void deleteNote(int row, int col, int number) {
        if (isValidCell(row, col) && isValidNumber(number)) {
            notes[row][col][number] = 0;
        }
        else {
            cout << "������������ ����" << endl;
        }
    }

    //����� ���� �������
    void printNotes(int row, int col) {
        if (isValidCell(row, col)) {
            cout << "������� ��� ������ (" << row << ", " << col << "): ";
            for (int num : notes[row][col]) {
                if (num != 0) {
                    cout << num << "; ";
                }
            }
            cout << endl;
        }
        else {
            cout << "������������ ����!" << endl;
        }
    }

private:
    bool isValidNumber(int number) {
        return number >= 1 && number <= 9;
    }

    bool isValidCell(int row, int col) {
        return row >= 1 && row <= 9 && col >= 1 && col <= 9;
    }
};
