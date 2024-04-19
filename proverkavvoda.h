#pragma once
#include <iostream>

using namespace std; 

void proverka(int* znach) {

    while (cin.fail() || *znach < 1 || *znach > 9) {
        // Очищаем флаг ошибки ввода
        cin.clear();
        // Очищаем буфер ввода до новой строки
        while (cin.get() != '\n') continue;

        cout << "Ошибка! Введите корректное число от 1 до 9: ";
        cin >> *znach;
    }


}