// ПЗ 5_6. Одномерные и многомерные массивы
// 5.1 (в аудитории): динамические одномерные массивы, цикл через дополнительный указатель
// 5.2 (самостоятельно): двумерные массивы, работа с файлами
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// ---------- 5.1.1 Количество элементов, больших среднего арифметического ----------
void task511() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int* p = a; p < a + n; p++) cin >> *p;

    double sum = 0;
    for (int* p = a; p < a + n; p++) sum += *p;
    double avg = sum / n;

    int cnt = 0;
    for (int* p = a; p < a + n; p++)
        if (*p > avg) cnt++;

    if (cnt == 0) cout << "Нет элементов в массиве строго больше среднего арифметического" << endl;
    else cout << cnt << endl;
    delete[] a;
}

// ---------- 5.1.2 Количество строгих локальных максимумов ----------
void task512() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int* p = a; p < a + n; p++) cin >> *p;

    int cnt = 0;
    for (int* p = a + 1; p < a + n - 1; p++)
        if (*p > *(p - 1) && *p > *(p + 1)) cnt++;

    if (cnt == 0) cout << "Нет строгих локальных максимумов" << endl;
    else cout << cnt << endl;
    delete[] a;
}

// ---------- 5.1.3 Невозрастающая или неубывающая последовательность ----------
void task513() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int* p = a; p < a + n; p++) cin >> *p;

    bool nonDecr = true, nonIncr = true;
    for (int* p = a + 1; p < a + n; p++) {
        if (*p < *(p - 1)) nonDecr = false;
        if (*p > *(p - 1)) nonIncr = false;
    }
    cout << (nonDecr || nonIncr ? "YES" : "NO") << endl;
    delete[] a;
}

// ---------- 5.1.4 Третий максимум (пузырьковая сортировка) ----------
void task514() {
    int n;
    cin >> n;
    int* a = new int[n];
    for (int* p = a; p < a + n; p++) cin >> *p;

    for (int i = 0; i < n - 1; i++)                 // пузырёк по возрастанию
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
            }

    for (int* p = a; p < a + n; p++) cout << *p << " ";
    cout << endl;

    // третий по величине среди различных значений
    int distinct = 1;
    int third = 0;
    bool found = false;
    for (int* p = a + n - 2; p >= a; p--) {
        if (*p != *(p + 1)) {
            distinct++;
            if (distinct == 3) { third = *p; found = true; break; }
        }
    }
    if (found) cout << third << endl;
    else cout << "Нет 3 максимума" << endl;
    delete[] a;
}

// ---------- 5.1.5 Обратная перестановка ----------
void task515() {
    int n;
    cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) b[a[i] - 1] = i + 1;   // гость i+1 сел на место a[i]
    for (int* p = b; p < b + n; p++) cout << *p << " ";
    cout << endl;
    delete[] a;
    delete[] b;
}

// ---------- 5.2.1 Звёздочка ----------
void task521() {
    int n;
    cin >> n;
    char a[15][15];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) a[i][j] = '.';
    for (int i = 0; i < n; i++) {
        a[n / 2][i] = '*';          // средняя строка
        a[i][n / 2] = '*';          // средний столбец
        a[i][i] = '*';              // главная диагональ
        a[i][n - 1 - i] = '*';      // побочная диагональ
    }
    ofstream fout("output.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << a[i][j];
            if (j < n - 1) fout << " ";
        }
        fout << endl;
    }
}

// ---------- 5.2.2 Симметрия ----------
void task522() {
    int n;
    cin >> n;
    ofstream fout("output.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << abs(i - j);
            if (j < n - 1) fout << " ";
        }
        fout << endl;
    }
}

// ---------- 5.2.3 Кинотеатр ----------
void task523() {
    ifstream fin("input.txt");
    int n, m;
    fin >> n >> m;
    vector<vector<int>> seats(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) fin >> seats[i][j];
    int k;
    fin >> k;

    int answer = 0;
    for (int i = 0; i < n && answer == 0; i++) {
        int run = 0;
        for (int j = 0; j < m; j++) {
            if (seats[i][j] == 0) run++;
            else run = 0;
            if (run >= k) { answer = i + 1; break; }
        }
    }
    cout << answer << endl;
}

// ---------- 5.2.4 Сапёр ----------
void task524() {
    ifstream fin("input.txt");
    int m, n, k;
    fin >> m >> n >> k;
    vector<vector<int>> field(m, vector<int>(n, 0));   // -1 - мина
    for (int t = 0; t < k; t++) {
        int r, c;
        fin >> r >> c;
        field[r - 1][c - 1] = -1;
    }
    ofstream fout("output.txt");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (field[i][j] == -1) fout << "*";
            else {
                int cnt = 0;
                for (int di = -1; di <= 1; di++)
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && field[ni][nj] == -1) cnt++;
                    }
                fout << cnt;
            }
            if (j < n - 1) fout << " ";
        }
        fout << endl;
    }
}

// ---------- 5.2.5 Возведение в степень (длинное число, цифры в массиве) ----------
// число хранится «наоборот»: цифра единиц в элементе 0
vector<int> multiply(const vector<int>& x, const vector<int>& y) {
    vector<int> res(x.size() + y.size(), 0);
    for (size_t i = 0; i < x.size(); i++)
        for (size_t j = 0; j < y.size(); j++)
            res[i + j] += x[i] * y[j];
    for (size_t i = 0; i + 1 < res.size(); i++) {      // переносы
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

void task525() {
    ifstream fin("input.txt");
    string number;
    int p;
    fin >> number >> p;
    vector<int> base;
    for (int i = (int)number.size() - 1; i >= 0; i--) base.push_back(number[i] - '0');

    vector<int> result(1, 1);                           // 1
    for (int i = 0; i < p; i++) result = multiply(result, base);

    ofstream fout("output.txt");
    for (int i = (int)result.size() - 1; i >= 0; i--) fout << result[i];
    fout << endl;
}

int main() {
    int task;
    cout << "Задание: 1-5 (5.1.x в аудитории), 6-10 (5.2.x самостоятельно): ";
    cin >> task;
    switch (task) {
        case 1: task511(); break;
        case 2: task512(); break;
        case 3: task513(); break;
        case 4: task514(); break;
        case 5: task515(); break;
        case 6: task521(); break;
        case 7: task522(); break;
        case 8: task523(); break;
        case 9: task524(); break;
        case 10: task525(); break;
        default: cout << "Нет такого задания" << endl;
    }
    return 0;
}
