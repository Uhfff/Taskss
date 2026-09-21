// ПЗ 3_4. Операторы цикла (массивы и строки для работы с числами не используются)
// Задания: 5.1 Акция, 5.2 Чётные числа, 5.3 Вставить цифру, 5.4 Мы делили апельсин, 5.5 Числовая змейка
#include <iostream>
#include <iomanip>
using namespace std;

// 5.1 Акция: скидка 10% на товары от 500, ввод заканчивается нулём
void task51() {
    double price, sum = 0;
    while (cin >> price && price != 0) {
        if (price >= 500) sum += price * 0.9;
        else sum += price;
    }
    cout << fixed << setprecision(2) << sum << endl;
}

// Разворот числа: возвращает перевёрнутое число, в len кладёт количество цифр исходного
long long reverseNumber(long long n, int& len) {
    long long rev = 0;
    len = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
        len++;
    }
    return rev;
}

// 5.2 Убрать все чётные цифры
void task52() {
    long long n;
    cin >> n;
    int len;
    long long rev = reverseNumber(n, len);   // теперь цифры идут слева направо при взятии %10
    bool any = false;
    for (int i = 0; i < len; i++) {
        int d = rev % 10;
        rev /= 10;
        if (d % 2 != 0) { cout << d; any = true; }
    }
    if (!any) cout << 0;
    cout << endl;
}

// 5.3 После каждой нечётной цифры вставить цифру 8
void task53() {
    long long n;
    cin >> n;
    int len;
    long long rev = reverseNumber(n, len);
    for (int i = 0; i < len; i++) {
        int d = rev % 10;
        rev /= 10;
        cout << d;
        if (d % 2 != 0) cout << 8;
    }
    cout << endl;
}

// 5.4 Апельсин: все способы разделить n долек между тремя (каждому не меньше одной)
void task54() {
    int n;
    cin >> n;
    cout << "А Б В" << endl;
    for (int a = 1; a <= n - 2; a++)
        for (int b = 1; b <= n - a - 1; b++)
            cout << a << " " << b << " " << n - a - b << endl;
}

int digitsCount(int x) {
    int c = 0;
    while (x > 0) { c++; x /= 10; }
    return c;
}

// 5.5 Числовая змейка: столбцы заполняются сверху вниз, затем снизу вверх и т.д.
void task55() {
    int n, m;
    cin >> n >> m;                       // n - высота, m - ширина
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int value;
            if (j % 2 == 0) value = j * n + i + 1;    // сверху вниз
            else value = j * n + (n - i);             // снизу вверх
            int width = digitsCount((j + 1) * n);     // ширина столбца - по его наибольшему числу
            cout << setw(width) << value;
            if (j < m - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int task;
    cout << "Выберите задание (1-5): ";
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
