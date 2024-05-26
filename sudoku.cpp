#include <cstdlib> // для использования rand()
#include <ctime>
#include <windows.h>
#include <iomanip>
#include "generationsudoku.h"
#include "notes.h"
#include "proverkavvoda.h"
#include <algorithm>
using namespace std;

int main() {
    srand(time(0));
    setlocale(LC_ALL, "ru");
    vector<vector<vector<int>>> easy{
        {{1, 1, 0, 1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 0, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 1, 1}}, 
        {{0,1,0,1,0,1,0,1,0},
        {0,0,1,0,1,1,0,1,0},
        {1,1,1,0,0,1,1,0,0},
        {0,1,0,1,0,1,0,0,1},
        {1,1,1,0,1,0,1,0,0},
        {1,0,0,1,0,0,0,1,0},
        {0,0,1,1,1,1,0,1,1},
        {0,0,0,0,0,0,1,1,1},
        {1,1,1,0,1,0,0,0,0}
        },
        {{1,0,1,0,1,1,1,0,0},
        {1,0,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,1,0,1},
        {0,0,0,1,0,0,1,0,0},
        {0,1,1,1,0,0,0,1,1},
        {1,1,0,1,0,1,0,0,0},
        {1,1,0,0,0,1,0,0,1},
        {1,1,1,0,1,1,1,0,0},
        {1,1,0,0,0,1,1,1,1}
        }
    };
    vector<vector<vector<int>>> middle{ {
    {1, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 1},
    {0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 1}
    },
    {{0,0,0,1,0,1,1,0,1},
    {0,0,1,0,0,0,0,1,0},
    {1,0,0,0,1,1,0,0,0},
    {1,1,0,0,1,1,1,1,1},
    {1,1,0,1,0,0,0,0,0},
    {1,1,0,1,1,1,1,1,0},
    {1,0,1,0,0,0,1,1,0},
    {0,0,1,0,1,0,1,0,1},
    {1,0,0,1,0,0,0,0,0}},
    {{1,0,0,1,1,0,0,0,0},
{1,1,0,1,0,1,0,0,0},
{1,1,0,1,1,1,1,1,0},
{0,0,1,1,1,1,0,0,0},
{0,0,1,1,1,0,0,0,1},
{0,0,1,1,0,1,0,0,0},
{0,0,0,0,0,0,1,0,1},
{0,0,0,1,0,0,1,1,1},
{0,1,1,1,1,1,1,1,0}

}

    };
    vector<vector<vector<int>>> hard{ {
{0, 1, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 0, 1, 1, 0, 0},
{0, 0, 1, 0, 1, 0, 0, 0, 1},
{0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 1, 1}},
        {{0,0,0,0,1,0,0,0,1},
{0,0,0,0,1,0,1,1,0},
{0,1,1,1,0,1,1,0,1},
{1,1,0,1,0,0,1,1,0},
{0,1,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,0,0},
{1,0,0,0,0,1,1,1,0},
{1,0,1,1,0,0,0,0,0},
{0,0,1,1,0,0,0,1,0}},
        {{1,0,1,0,1,1,0,0,0},
{0,0,0,1,0,1,0,0,1},
{0,1,0,0,0,0,0,1,0},
{1,0,1,1,0,0,0,1,0},
{0,1,1,0,0,0,0,1,1},
{0,0,0,0,1,0,0,0,1},
{1,1,1,1,0,1,1,0,1},
{0,0,0,0,1,0,1,0,1},
{0,1,1,1,1,1,1,0,1}}
    };

    vector<vector<int>> table1;

    string hellou, deystv, slojnost, zamet;
    int str, stb, chl, str2, stb2, chislozam;

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




    while (true) {
        deystv = " ";
        int k = 0;
        int var_slojnosti;
        generation example;
        Notes sudokuNotes;
        example.mix();
        table1 = example.table;
        cout << "Выберите уровень сложности: " << "\n" << "[E] - простой" << "\n" << "[M] - средний" << "\n" << "[H] - сложный" << "\n";
        cin >> slojnost;
        while (true) {
            if (slojnost == "E") {
                var_slojnosti = rand() % (easy.size());
                for (size_t i = 0; i < easy[var_slojnosti].size(); ++i) {
                    for (size_t j = 0; j < easy[var_slojnosti][i].size(); ++j) {
                        if (easy[var_slojnosti][i][j] == 0) {
                            example.table[i][j] = 0;
                        }
                    }
                }
                system("cls");
                break;
            }
            if (slojnost == "M") {
                var_slojnosti = rand() % (middle.size());
                for (size_t i = 0; i < middle[var_slojnosti].size(); ++i) {
                    for (size_t j = 0; j < middle[var_slojnosti][i].size(); ++j) {
                        if (middle[var_slojnosti][i][j] == 0) {
                            example.table[i][j] = 0;
                        }
                    }
                }
                system("cls");
                break;
            }
            if (slojnost == "H") {
                var_slojnosti = rand() % (hard.size());
                for (size_t i = 0; i < hard[var_slojnosti].size(); ++i) {
                    for (size_t j = 0; j < hard[var_slojnosti][i].size(); ++j) {
                        if (hard[var_slojnosti][i][j] == 0) {
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
                    if (k == 1) {
                        cout << "Неверное число. Осталось " << 3 - k << " ошибки" << "\n";
                    }
                    else if (k == 2) {
                        cout << "Неверное число. Осталась " << 3 - k << " ошибка" << "\n";
                    }
                    else if (k == 3) {
                        cout << "Неверное число. Лимит ошибок исчерпан" << "\n";
                    }
                       
                    if (k > 3) {
                        cout << "Вы привысили лимит ошибок. Вы можете начать игру заново [U] или покинуть ее [L] " << "\n";
                        cin >> deystv;

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
                        
                    while ((zamet != "B" && zamet != "+" && zamet != "-" && zamet != "?")) {
                        cout << "Выберите действие:" << "\n";
                        cin >> zamet;
                    }

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
                    proverka(&stb2);
                       
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


    
    return 0;
}


