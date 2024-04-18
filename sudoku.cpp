#include <vector>
#include <functional>
#include <cstdlib> // для использования rand()
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <limits>
#include <iomanip>


using namespace std; 

class Grid {
public:
    int n = 3;
    vector<vector<int>> table;
    Grid(int n = 3) : n(n) {
        // Генерация базовой таблицы
        table.resize(n * n, vector<int>(n * n));
        for (int i = 0; i < n * n; i++) {
            for (int j = 0; j < n * n; j++) {
                table[i][j] = (i * n + i / n + j) % (n * n) + 1;
            }
        }
    }

    ~Grid() {}

    void show() {
        int k = 0;
        cout << "\033[31;1m" << "   1 2 3   4 5 6   7 8 9" << "\033[0m " << endl;
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {  // добавляем разделитель после каждого блока
                for (int k = 0; k < 25; k++) {
                    cout << "-";
                }
                cout << endl;
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {  // добавляем разделитель внутри блока
                    cout << "| ";
                }
                if (j == 0) {
                    cout << "\033[31;1m" << ++k << "\033[0m " << " ";
                }
                if (table[i][j] == 0) {  // если значение ячейки равно 0
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
        /* Transposing the whole grid */
        std::vector<std::vector<int>> newTable;
        newTable.resize(table[0].size(), std::vector<int>(table.size()));

        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table[0].size(); j++) {
                newTable[j][i] = table[i][j];
            }
        }

        table = newTable;
    }

    void swap_rows_small() {
        /* Swap the two rows */
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
        /* Swap the two area horizon */
        int area1 = rand() % n;

        int area2 = rand() % n;
        while (area1 == area2) {
            area2 = rand() % n;
        }

        for (int i = 0; i < n; i++) {
            int N1 = area1 * n + i;
            int N2 = area2 * n + i;

            std::swap(table[N1], table[N2]);
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


class Notes {
private:
    std::vector<std::vector<std::vector<int>>> notes; // Вектор для хранения заметок

public:
    // Конструктор класса
    Notes() {
        // Инициализация вектора заметок
        notes = std::vector<std::vector<std::vector<int>>>(10, std::vector<std::vector<int>>(10, std::vector<int>(10, 0)));
    }

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
                    std::cout << num << " ";
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


void proverka(int *znach) {

    while (cin.fail() || *znach < 1 || *znach > 9) {
        // Очищаем флаг ошибки ввода
        cin.clear();
        // Очищаем буфер ввода до новой строки
        while (cin.get() != '\n') continue;

        cout << "Ошибка! Введите корректное число от 1 до 9: ";
        cin >> *znach;
    }


}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "ru");
    vector<std::vector<int>> easy{
        {1, 1, 0, 1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 1}
    };
    std::vector<std::vector<int>> middle{
    {1, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 1},
    {0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 1}
    };
    std::vector<std::vector<int>> hard{
{0, 1, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 1, 1}
    };

    vector<std::vector<int>> table1;

    string hellou, deystv, slojnost, zamet;
    cout << setw((95)) << "Добро пожаловать в игру Судоку" << "\n" << setw((95)) << "Введите команду для продолжения" << "\n" << "\n";
    cout << setw(83) << "START" << "\n" << setw(83) << "LEAVE" << "\n";
    cin >> hellou;

    while (true) {
        if (hellou == "LEAVE") {
            exit(0);
            break;
        }
        if (hellou == "START") {
            system("cls");
            break;
        }
        else if (hellou != "START") {
            cout << "Введите START или LEAVE" << "\n";;
            cin >> hellou;
            continue;
        }

    }

    /*while (true) {

    }*/

    /*vector<vector<int>> flook(example.n * example.n, vector<int>(example.n * example.n, 0));*/


    deystv = "U";
    int str, stb, chl, str2, stb2, chislozam;

    while (true) {
        if (deystv == "U") {
            deystv = " ";
            int k = 0;
            Grid example;
            Notes sudokuNotes;
            example.mix();
            table1 = example.table;
            cout << "Выберите уровень сложности: " << "\n" << "[E] - простой" << "\n" << "[M] - средний" << "\n" << "[H] - сложный" << "\n";
            cin >> slojnost;
            while (true) {
                if (slojnost == "E") {
                    for (size_t i = 0; i < easy.size(); ++i) {
                        for (size_t j = 0; j < easy[i].size(); ++j) {
                            if (easy[i][j] == 0) {
                                example.table[i][j] = 0;
                            }
                        }
                    }
                    system("cls");
                    break;
                }
                if (slojnost == "M") {
                    for (size_t i = 0; i < middle.size(); ++i) {
                        for (size_t j = 0; j < middle[i].size(); ++j) {
                            if (middle[i][j] == 0) {
                                example.table[i][j] = 0;
                            }
                        }
                    }
                    system("cls");
                    break;
                }
                if (slojnost == "H") {
                    for (size_t i = 0; i < hard.size(); ++i) {
                        for (size_t j = 0; j < hard[i].size(); ++j) {
                            if (hard[i][j] == 0) {
                                example.table[i][j] = 0;
                            }
                        }
                    }
                    system("cls");
                    break;
                }
                else if (slojnost != "E" or slojnost != "M" or slojnost != "H") {
                    cout << "Введите уровень сложности" << "\n";;
                    cin >> slojnost;
                    continue;
                }

            }
            cout << "[L] - завершить игру" << "\n" << "[U] - начать игру заново" << "\n" << "[N] - работа с заметками" << "\n" << "[0] - ввод числа" << "\n" << "\n";
            example.show();

            while (deystv != "U") {

                cin >> deystv;

                if (deystv == "0") {
                    cout << "Введите строку" << "\n";
                    cin >> str;

                    proverka(&str);

                    cout << "Введите столбец" << "\n";
                    cin >> stb;
                    proverka(&stb);
                    cout << "Введите число" << "\n";
                    cin >> chl;
                    proverka(&chl);
                    if (chl == table1[str - 1][stb - 1]) {
                        example.table[str - 1][stb - 1] = chl;

                        bool hasZero = false;
                        for (const auto& row : example.table) {
                            for (int num : row) {
                                if (num == 0) {
                                    hasZero = true;
                                    break;
                                }
                            }
                            if (hasZero) {
                                system("cls");
                                cout << "[L] - завершить игру" << "\n" << "[U] - начать игру заново" << "\n" << "[N] - работа с заметками" << "\n" << "[0] - ввод числа" << "\n" << "\n";
                                example.show();
                                break;
                            }
                        }
                        if (!hasZero) {
                            cout << "Поздравляю, вы прошли игру! Вы можете начать игру заново [U] или покинуть ее [L]";
                            cin >> deystv;
                        
                            
                        }

                    }
                    else {
                        k++;
                        cout << "Неверное число. Осталось " << 3 - k << " ошибки" << "\n";
                        if (k > 3) {
                            cout << "Вы привысили лимит ошибок. Игра завершена. " << "\n";
                            exit(0);
                            break;
                        }
                        Sleep(5000);
                        system("cls");
                        cout << "[L] - завершить игру" << "\n" << "[U] - начать игру заново" << "\n" << "[N] - работа с заметками" << "\n" << "[0] - ввод числа" << "\n" << "\n";
                        example.show();
                    }
                }
                if (deystv == "N") {
                    while (true){
                        cout << "Режим работы с заметками:" << "\n";
                        cout << "[+] - создать заметку" << "\n" << "[?] - просмотреть заметку" << "\n" << "[-] - удалить заметки" << "\n" << "[B] - выйти" << "\n";
                        cout << "Выберите действие:" << "\n";
                        cin >> zamet;

                        if (zamet == "B") {
                            Sleep(5000);
                            system("cls");
                            cout << "[L] - завершить игру" << "\n" << "[U] - начать игру заново" << "\n" << "[N] - работа с заметками" << "\n" << "[0] - ввод числа" << "\n" << "\n";
                            example.show();
                            break;

                        }

                        cout << "Введите строку" << "\n";
                        cin >> str2;
                        proverka(&str2);

                        cout << "Введите столбец" << "\n";
                        cin >> stb2;
                        while (cin.fail() || stb2 < 1 || stb2 > 9) {
                            // Очищаем флаг ошибки ввода
                            cin.clear();
                            // Очищаем буфер ввода до новой строки
                            while (cin.get() != '\n') continue;

                            cout << "Ошибка! Введите корректное число от 1 до 9: ";
                            cin >> stb2;
                        }
                       
                        if (zamet == "+") {
                            cout << "Введите число" << "\n";
                            cin >> chislozam;
                            proverka(&chislozam);
                            sudokuNotes.addNote(str2, stb2, chislozam);
                        }
                        if (zamet == "?") {
                            sudokuNotes.printNotes(str2, stb2);
                        }

                        if (zamet == "-") {
                            cout << "Введите число" << "\n";
                            cin >> chislozam;
                            proverka(&chislozam);
                            sudokuNotes.deleteNote(str2, stb2, chislozam);
                        }
                        if (zamet == "B") {
                            Sleep(3000);
                            system("cls");
                            cout << "[L] - завершить игру" << "\n" << "[U] - начать игру заново" << "\n" << "[N] - работа с заметками" << "\n" << "[0] - ввод числа" << "\n" << "\n";
                            example.show();
                            break;

                        }

                    }
                }
            
                if (deystv == "L") {
                    exit(0);
                    break;
                }



                }
            }

        /*for (int i = 0; i < example.n * example.n; i++) {
            for (int j = 0; j < example.n * example.n; j++) {
                cout << example.table[i][j] << " ";
            }
            cout << endl;
        }*/
        //cout << "---------------------------------------------- ";

        //    }
        //    cout << endl;
        //}

       /* int i = rand() % (example.n * example.n);
        int j = rand() % (example.n * example.n);
        flook[i][j] == 0*/;


        /*while (iterator < pow(example.n, 4)) {
            int i = rand() % (example.n * example.n);
            int j = rand() % (example.n * example.n);

            if (flook[i][j] == 0) {
                iterator++;
                flook[i][j] = 1;

                int temp = example.table[i][j];
                example.table[i][j] = 0;
                difficult--;

                vector<vector<int>> table_solution;
                for (int copy_i = 0; copy_i < example.n * example.n; copy_i++) {
                    table_solution.push_back(example.table[copy_i]);
                }

                int i_solution = 0;
                for (auto solution : solver.solve_sudoku(make_pair(example.n, example.n), table_solution)) {
                    i_solution++;
                }

                if (i_solution != 1) {
                    example.table[i][j] = temp;
                    difficult++;
                }
            }
        }*/
    }
}


