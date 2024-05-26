#pragma once
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class generation {
public:
    int n = 3;
    vector<vector<int>> table;
    generation(int n = 3) : n(n) {
        // √енераци€ базовой таблицы
        table.resize(n * n, vector<int>(n * n));
        for (int i = 0; i < n * n; i++) {
            for (int j = 0; j < n * n; j++) {
                table[i][j] = (i * n + i / n + j) % (n * n) + 1;
            } 
        }
    }


    void show() {
        int k = 0;
        cout << "\033[31;1m" << "   1 2 3   4 5 6   7 8 9" << "\033[0m " << endl;
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {  // добавл€ем разделитель после каждого блока
                for (int k = 0; k < 25; k++) {
                    cout << "-";
                }
                cout << endl;
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {  // добавл€ем разделитель внутри блока
                    cout << "| ";
                }
                if (j == 0) {
                    cout << "\033[31;1m" << ++k << "\033[0m " << " ";
                }
                if (table[i][j] == 0) {  // если значение €чейки равно 0
                    cout << "\033[32;1m" << table[i][j] << "\033[0m ";  // выводим зеленым цветом
                }
                else {
                    cout << "\033[33;1m" << table[i][j] << "\033[0m ";  // выводим желтым цветом
                }

            }
            cout << endl;
        }
        cout << endl;
    }


    void transposing() {
        vector<vector<int>> newTable(9, vector<int>(9));
        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table[0].size(); j++) {
                newTable[j][i] = table[i][j];
            }
        }

        table = newTable;
    }

    void swap_rows_small() {
        int area = rand() % n;
        int line1 = rand() % n;

        int N1 = area * n + line1;

        int line2 = rand() % n;
        while (line1 == line2) {
            line2 = rand() % n;
        }

        int N2 = area * n + line2;

        swap(table[N1], table[N2]);
    }

    void swap_columns_small() {
        transposing();
        swap_rows_small();
        transposing();
    }

    void swap_rows_area() {
        int area1 = rand() % n;

        int area2 = rand() % n;
        while (area1 == area2) {
            area2 = rand() % n;
        }

        for (int i = 0; i < n; i++) {
            int N1 = area1 * n + i;
            int N2 = area2 * n + i;

            swap(table[N1], table[N2]);
        }
    }

    void swap_columns_area() {
        transposing();
        swap_rows_area();
        transposing();
    }

    void mix(int amt = 10) {
        vector<function<void()>> mixFunc = {
            [&]() { transposing(); },
            [&]() { swap_rows_small(); },
            [&]() { swap_columns_small(); },
            [&]() { swap_rows_area(); },
            [&]() { swap_columns_area(); }
        };

        for (int i = 1; i < amt; i++) {
            int idFunc = rand() % mixFunc.size();
            mixFunc[idFunc]();
        }
    }

private:

};
