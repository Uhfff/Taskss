// ПЗ 9. Организация подпрограмм
// Общие требования: динамические массивы, адресная арифметика, независимый интерфейс функций
// (никаких глобальных переменных внутри функций), массивы передаются указателями.
// Задания: 5.1 Двухмерный массив, 5.2 Функция (указатели на функции + меню),
//          5.3 Массив любой размерности, 5.4 Морской бой, 5.5 Ход конём.
// В 5.2 функция №7 записана как ln^2((x-1)/x) - в PDF условие читается неоднозначно.
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// ============ Общие функции для двумерных массивов ============
int** createMatrix(int n, int m) {
    int** a = new int*[n];
    for (int i = 0; i < n; i++) a[i] = new int[m];
    return a;
}

void deleteMatrix(int** a, int n) {
    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

void fillRandom(int** a, int n, int m, int lo, int hi) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(*(a + i) + j) = lo + rand() % (hi - lo + 1);       // адресная арифметика
}

void printMatrix(int** a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << *(*(a + i) + j) << "\t";
        cout << endl;
    }
}

// ============ 5.1 Сумма элементов, кратных 5 и не кратных 2 ============
bool sumMultiple5NotEven(int** a, int n, int m, int& sum) {
    sum = 0;
    bool found = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int v = *(*(a + i) + j);
            if (v % 5 == 0 && v % 2 != 0) { sum += v; found = true; }
        }
    return found;
}

void task51() {
    int n, m;
    cout << "N, M (10..1000): ";
    cin >> n >> m;
    if (n < 10 || m < 10 || n > 1000 || m > 1000) { cout << "Неверные размеры" << endl; return; }
    int** a = createMatrix(n, m);
    fillRandom(a, n, m, 0, 99);
    if (n <= 20 && m <= 20) printMatrix(a, n, m);
    int s;
    if (sumMultiple5NotEven(a, n, m, s)) cout << "Сумма: " << s << endl;
    else cout << "Таких элементов нет" << endl;
    deleteMatrix(a, n);
}

// ============ 5.2 Указатели на функции и меню ============
// Каждая функция возвращает false, если значение в точке x вычислить нельзя.
bool f1(double x, double& r) { r = 1 / (1 + x * x); return true; }
bool f2(double x, double& r) { if (x < 0 || x > 1) return false; r = acos(sqrt(x)); return true; }
bool f3(double x, double& r) { if (x <= -1 || x >= 1) return false; r = log((1 + x) / (1 - x)); return true; }
bool f4(double x, double& r) { r = exp(x) - 1; return true; }
bool f5(double x, double& r) { if (x < 0) return false; r = sin(sqrt(x)); return true; }
bool f6(double x, double& r) { if (x == 0) return false; r = atan(1 / x); return true; }
bool f7(double x, double& r) {
    if (x == 0) return false;
    double t = (x - 1) / x;
    if (t <= 0) return false;
    double l = log(t);
    r = l * l;
    return true;
}

void task52() {
    bool (*funcs[7])(double, double&) = { f1, f2, f3, f4, f5, f6, f7 };
    const char* names[7] = { "1/(1+x^2)", "arccos(sqrt(x))", "ln((1+x)/(1-x))", "e^x-1",
                             "sin(sqrt(x))", "arctg(1/x)", "ln^2((x-1)/x)" };
    int choice;
    do {
        cout << "\nМЕНЮ\n";
        for (int i = 0; i < 7; i++) cout << i + 1 << ". " << names[i] << endl;
        cout << "0. Выход\nВыбор: ";
        cin >> choice;
        if (choice >= 1 && choice <= 7) {
            double x, r;
            cout << "x = ";
            cin >> x;
            if (funcs[choice - 1](x, r)) cout << "Результат: " << r << endl;
            else cout << "Функция в точке x не определена" << endl;
        }
    } while (choice != 0);
}

// ============ 5.3 Массив любой размерности ============
// Изменение размера: новая матрица, старые элементы копируются, новые = 0
int** resizeMatrix(int** a, int n, int m, int newN, int newM) {
    int** b = createMatrix(newN, newM);
    for (int i = 0; i < newN; i++)
        for (int j = 0; j < newM; j++)
            b[i][j] = (i < n && j < m) ? a[i][j] : 0;
    deleteMatrix(a, n);
    return b;
}

// Вывод подматрицы: строки r1..r2, столбцы c1..c2 (нумерация с 0)
void printSubMatrix(int** a, int n, int m, int r1, int r2, int c1, int c2) {
    if (r1 < 0 || c1 < 0 || r2 >= n || c2 >= m || r1 > r2 || c1 > c2) {
        cout << "Неверные границы подматрицы" << endl;
        return;
    }
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <= c2; j++) cout << a[i][j] << "\t";
        cout << endl;
    }
}

void addNumber(int** a, int n, int m, int k) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) a[i][j] += k;
}

void multiplyNumber(int** a, int n, int m, int k) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) a[i][j] *= k;
}

void task53() {
    int n, m;
    cout << "N, M (10..1000): ";
    cin >> n >> m;
    if (n < 10 || m < 10 || n > 1000 || m > 1000) { cout << "Неверные размеры" << endl; return; }
    int** a = createMatrix(n, m);
    fillRandom(a, n, m, 0, 9);
    int choice;
    do {
        cout << "\n1. Изменить размер\n2. Показать всю матрицу\n3. Показать подматрицу\n"
                "4. Прибавить число\n5. Умножить на число\n0. Выход\nВыбор: ";
        cin >> choice;
        if (choice == 1) {
            int nn, nm;
            cout << "Новые N, M: ";
            cin >> nn >> nm;
            if (nn > 0 && nm > 0) { a = resizeMatrix(a, n, m, nn, nm); n = nn; m = nm; }
        } else if (choice == 2) {
            printMatrix(a, n, m);
        } else if (choice == 3) {
            int r1, r2, c1, c2;
            cout << "Строки от, до; столбцы от, до (с 0): ";
            cin >> r1 >> r2 >> c1 >> c2;
            printSubMatrix(a, n, m, r1, r2, c1, c2);
        } else if (choice == 4) {
            int k; cout << "Число: "; cin >> k; addNumber(a, n, m, k);
        } else if (choice == 5) {
            int k; cout << "Число: "; cin >> k; multiplyNumber(a, n, m, k);
        }
    } while (choice != 0);
    deleteMatrix(a, n);
}

// ============ 5.4 Морской бой в одни ворота ============
const int SZ = 10;

// можно ли поставить корабль длиной len с верхней/левой клетки (r,c); горизонтальный или вертикальный
bool canPlace(char f[SZ][SZ], int r, int c, int len, bool horiz) {
    for (int k = 0; k < len; k++) {
        int rr = r + (horiz ? 0 : k), cc = c + (horiz ? k : 0);
        if (rr >= SZ || cc >= SZ) return false;
        for (int di = -1; di <= 1; di++)                 // вокруг не должно быть других кораблей
            for (int dj = -1; dj <= 1; dj++) {
                int ni = rr + di, nj = cc + dj;
                if (ni >= 0 && ni < SZ && nj >= 0 && nj < SZ && f[ni][nj] == '*') return false;
            }
    }
    return true;
}

void placeShips(char f[SZ][SZ]) {
    for (int i = 0; i < SZ; i++)
        for (int j = 0; j < SZ; j++) f[i][j] = '.';
    int lens[6] = { 3, 2, 2, 1, 1, 1 };
    for (int s = 0; s < 6; s++) {
        while (true) {
            int r = rand() % SZ, c = rand() % SZ;
            bool horiz = rand() % 2 == 0;
            if (canPlace(f, r, c, lens[s], horiz)) {
                for (int k = 0; k < lens[s]; k++) f[r + (horiz ? 0 : k)][c + (horiz ? k : 0)] = '*';
                break;
            }
        }
    }
}

void printField(char f[SZ][SZ]) {
    cout << "  ";
    for (int j = 0; j < SZ; j++) cout << j + 1 << " ";
    cout << endl;
    for (int i = 0; i < SZ; i++) {
        cout << (char)('A' + i) << " ";
        for (int j = 0; j < SZ; j++) cout << f[i][j] << " ";
        cout << endl;
    }
}

// сбор клеток корабля, содержащего (r,c), в массив cells; возвращает количество клеток
int collectShip(char ships[SZ][SZ], int r, int c, int cells[][2]) {
    int cnt = 0;
    int dr[4] = { -1, 1, 0, 0 }, dc[4] = { 0, 0, -1, 1 };
    cells[cnt][0] = r; cells[cnt][1] = c; cnt++;
    for (int d = 0; d < 4; d++) {
        int rr = r + dr[d], cc = c + dc[d];
        while (rr >= 0 && rr < SZ && cc >= 0 && cc < SZ && ships[rr][cc] == '*') {
            cells[cnt][0] = rr; cells[cnt][1] = cc; cnt++;
            rr += dr[d]; cc += dc[d];
        }
    }
    return cnt;
}

void task54() {
    char ships[SZ][SZ], view[SZ][SZ];
    placeShips(ships);
    for (int i = 0; i < SZ; i++)
        for (int j = 0; j < SZ; j++) view[i][j] = '.';

    int totalDecks = 3 * 1 + 2 * 2 + 1 * 3, hits = 0;
    for (int shot = 1; shot <= 15 && hits < totalDecks; shot++) {
        char letter;
        int col;
        cout << "Выстрел " << shot << " (буква строки A-J и номер столбца 1-10, например B 5): ";
        cin >> letter >> col;
        int r = toupper(letter) - 'A', c = col - 1;
        if (r < 0 || r >= SZ || c < 0 || c >= SZ) { cout << "Неверные координаты" << endl; shot--; continue; }
        if (ships[r][c] == '*' && view[r][c] != '*') {
            view[r][c] = '*';
            hits++;
            int cells[3][2];
            int cnt = collectShip(ships, r, c, cells);
            bool dead = true;
            for (int k = 0; k < cnt; k++) if (view[cells[k][0]][cells[k][1]] != '*') dead = false;
            if (dead) {                                   // корабль потоплен - обводим 'x'
                for (int k = 0; k < cnt; k++)
                    for (int di = -1; di <= 1; di++)
                        for (int dj = -1; dj <= 1; dj++) {
                            int ni = cells[k][0] + di, nj = cells[k][1] + dj;
                            if (ni >= 0 && ni < SZ && nj >= 0 && nj < SZ && view[ni][nj] == '.') view[ni][nj] = 'x';
                        }
                cout << "Потоплен!" << endl;
            } else cout << "Попадание!" << endl;
        } else cout << "Мимо" << endl;
        printField(view);
    }
    cout << (hits == totalDecks ? "Вы победили!" : "Выстрелы закончились") << endl;
    cout << "Итоговое поле:" << endl;
    printField(ships);
}

// ============ 5.5 Ход конём ============
void knightBoard(char board[8][8], int col, int row) {          // col 0..7 (a..h), row 0..7 (1..8)
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) board[i][j] = '.';
    int dc[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dr[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    board[7 - row][col] = 'K';                                    // строка 8 печатается первой
    for (int k = 0; k < 8; k++) {
        int c = col + dc[k], r = row + dr[k];
        if (c >= 0 && c < 8 && r >= 0 && r < 8) board[7 - r][c] = '*';
    }
}

void task55() {
    string pos;
    cin >> pos;                                                   // например b6
    if (pos.size() != 2 || pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
        cout << "Неверная клетка" << endl;
        return;
    }
    char board[8][8];
    knightBoard(board, pos[0] - 'a', pos[1] - '1');
    ofstream fout("output.txt");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fout << board[i][j];
            if (j < 7) fout << " ";
        }
        fout << endl;
    }
}

int main() {
    srand((unsigned)time(nullptr));
    int task;
    cout << "Задание 5.x (1-5): ";
    cin >> task;
    switch (task) {
        case 1: task51(); break;
        case 2: task52(); break;
        case 3: task53(); break;
        case 4: task54(); break;
        case 5: task55(); break;
        default: cout << "Нет такого задания" << endl;
    }
    return 0;
}
