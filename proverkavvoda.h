#pragma once
#include <iostream>

using namespace std; 

void proverka(int* znach) {

    while (cin.fail() || *znach < 1 || *znach > 9) {
        cin.clear();
        while (cin.get() != '\n') continue;

        cout << "������� ���������� ����� �� 1 �� 9: ";
        cin >> *znach;
    }


}