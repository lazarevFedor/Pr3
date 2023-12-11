#include <iostream>
#include "Windows.h"
#include <ctime>

using namespace std;

int choise;
const int SIZEARR = 6;

int randArr() {
    return (rand() % 100) + 1;
}

void printArr(int arr[][SIZEARR]) {
    system("cls");
    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < SIZEARR; i++) {
        for (int j = 0; j < SIZEARR; j++) {
            destCoord.X = j * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(*(arr + i) + j);
            Sleep(100);
        }
        cout << "\n\n";
    }
}

void fillSnake(int arr[][SIZEARR]) {
    system("cls");
    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int top = 0, bottom = SIZEARR - 1, left = 0, right = SIZEARR - 1;
    while (left <= right && top <= bottom) {
        // Сверху вниз
        for (int i = top; i <= bottom; i++) {
            destCoord.X = left * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + i) + left) = randArr();
            cout << *(*(arr + i) + left);
            cout.flush();
            Sleep(100);
        }
        left++;
        // Снизу вверх
        for (int i = bottom; i >= top; i--) {
            destCoord.X = left * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + i) + left) = randArr();
            cout << *(*(arr + i) + left);
            cout.flush();
            Sleep(100);
        }
        left++;
    }
    destCoord.X = 0;
    destCoord.Y = SIZEARR * 2;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void fillSpiral(int arr[][SIZEARR]) {
    system("cls");
    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int num = 0;
    int top = 0, bottom = SIZEARR - 1, left = 0, right = SIZEARR - 1;
    while (left <= right && top <= bottom) {
        //Верхняя строка
        for (int i = left; i <= right; i++) {
            destCoord.X = i * 4;
            destCoord.Y = top * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + top) + i) = randArr();
            cout << *(*(arr + top) + i);
            cout.flush();
            Sleep(100);
        }
        top++;
        //Правый столбец
        for (int i = top; i <= bottom; i++) {
            destCoord.X = right * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + i) + right) = randArr();
            cout << *(*(arr + i) + right);
            cout.flush();
            Sleep(100);
        }
        right--;
        //Нижняя строка
        for (int i = right; i >= left; (i--)) {
            destCoord.X = i * 4;
            destCoord.Y = bottom * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + bottom) + i) = randArr();
            cout << *(*(arr + bottom) + i);
            cout.flush();
            Sleep(100);
        }
        bottom--;
        //Левый столбец
        for (int i = bottom; i >= top; i--) {
            destCoord.X = left * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(*(arr + i) + left) = randArr();
            cout << *(*(arr + i) + left);
            cout.flush();
            Sleep(100);
        }
        left++;
    }
    destCoord.X = 0;
    destCoord.Y = SIZEARR * 2;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void moveBlocs(int arr[][SIZEARR]) {
    cout << "\nВыберете способ смены\n-->> ";
    cin >> choise;
    // По часовой смена
    if (choise == 1) {
        for (int i = 0; i < (SIZEARR / 2); i++) {
            for (int j = 0; j < SIZEARR; j++) {
                swap(*(*(arr + i + (SIZEARR / 2)) + j), *(*(arr + i) + j));
            }
        }
        for (int i = 0; i < (SIZEARR / 2); i++) {
            for (int j = 0; j < (SIZEARR / 2); j++) {
                swap(*(*(arr + i + (SIZEARR / 2)) + j + (SIZEARR / 2)), *(*(arr + i) + j));
            }
        }
    }
    // По диагонали смена
    else if (choise == 2) {
        for (int i = 0; i < (SIZEARR / 2); i++) {
            for (int j = 0; j < SIZEARR; j++) {
                if (j < (SIZEARR / 2)) {
                    swap(*(*(arr + i) + j), *(*(arr + i + (SIZEARR / 2)) + j + (SIZEARR / 2)));
                }
                else {
                    swap(*(*(arr + i) + j), *(*(arr + i + (SIZEARR / 2)) + j - (SIZEARR / 2)));
                }
            }
        }
    }
    // Верхние и нижние смена
    else if (choise == 3) {
        for (int i = 0; i < (SIZEARR / 2); i++) {
            for (int j = 0; j < SIZEARR; j++) {
                swap(*(*(arr + i) + j), *(*(arr + i + (SIZEARR / 2)) + j));
            }
        }
    }
    // Правые и левые смена
    else if (choise == 4) {
        for (int i = 0; i < SIZEARR; i++) {
            for (int j = 0; j < (SIZEARR / 2); j++) {
                swap(*(*(arr + i) + j), *(*(arr + i) + j + (SIZEARR / 2)));
            }
        }
    }
    else {
        cout << "\nНеправильно выбран способ";
    }
}

void insert(int* ptr, int* end) {
    int j;
    for (int* i = ptr + 1; i <= end; i++) {
        if (*i < *(i - 1)) {
            for (j = *i; i > ptr && *(i - 1) > j; i--) {
                *i = *(i - 1);
            }
            *i = j;
        }

    }
}

void mathActions(int arr[][SIZEARR]) {
    char sign;
    int number;
    cout << "\nВведите действие('+', '-', '*', '/') и число\n";
    cin >> sign >> number;

    if (sign == '+') {
        for (int i = 0; i < SIZEARR; i++) {
            for (int j = 0; j < SIZEARR; j++)
                *(*(arr + i) + j) += number;
        }
    }
    else if (sign == '-') {
        for (int i = 0; i < SIZEARR; i++) {
            for (int j = 0; j < SIZEARR; j++)
                *(*(arr + i) + j) -= number;
        }
    }
    else if (sign == '*') {
        for (int i = 0; i < SIZEARR; i++) {
            for (int j = 0; j < SIZEARR; j++)
                *(*(arr + i) + j) *= number;
        }
    }
    else if (sign == '/') {
        for (int i = 0; i < SIZEARR; i++) {
            for (int j = 0; j < SIZEARR; j++)
                *(*(arr + i) + j) /= number;
        }
    }
    else {
        cout << "Неправильное число или знак";
    }
}

int main() {
    setlocale(0, "RU");
    int arr[SIZEARR][SIZEARR];
    int* ptr = *arr, * end = *arr + SIZEARR * SIZEARR - 1;
    while (true) {
        cout << "Какой пункт вы хотите выбрать?\n" <<
            "1) Заполнить массив\n" <<
            "2) Поменять блоки местами\n" <<
            "3) Отсортировать\n" <<
            "4) Действия с матрицей\n" <<
            "5) Вывести массив\n" <<
            "6) Выход\n-->> ";
        cin >> choise;
        switch (choise) {
        case 1:
            cout << "\nКаким спсобом заполнить?\n-->> ";
            cin >> choise;
            if (choise == 1) {
                fillSnake(arr);
            }
            else if (choise == 2) {
                fillSpiral(arr);
            }
            else
                cout << "\nНеправильно введено число\n";
            break;
        case 2:
            printArr(arr);
            moveBlocs(arr);
            printArr(arr);
            break;
        case 3:
            insert(ptr, end);
            printArr(arr);
            break;
        case 4:
            mathActions(arr);
            printArr(arr);
            break;
        case 5:
            printArr(arr);
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "Ошибка! Попробуйте снова\n";
            break;
        }
    }
    return 0;
}
