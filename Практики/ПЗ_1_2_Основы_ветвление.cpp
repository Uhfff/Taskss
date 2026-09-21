// ПЗ 1_2. Основные конструкции C++, операторы ветвления
// Решены задания: 5.1.4 Сложение, 5.1.5 Производительность рабочих, 5.2.5 Количество дней в месяце.
// (Задания 5.1.1-5.1.3 с формулами и 5.2.1-5.2.4 с рисунками в PDF передаются картинками,
//  их условие из текста не восстановить.)
#include <iostream>
using namespace std;

// 5.1.4 Сложение чисел без учёта переносов разряда
int addNoCarry(int a, int b) {
    int res = 0, mul = 1;
    while (a > 0 || b > 0) {
        res += ((a % 10 + b % 10) % 10) * mul;   // складываем цифры, перенос отбрасываем
        mul *= 10;
        a /= 10;
        b /= 10;
    }
    return res;
}

// 5.1.5 3 работника собирают 3 изделия за 3 часа => 1 работник за 1 час делает 1/3 изделия
long long products(long long h, long long k) {
    return h * k / 3;
}

// 5.2.5 Количество дней в месяце (switch)
bool isLeap(int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }

int daysInMonth(int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeap(y) ? 29 : 28;
        default:
            return 0;
    }
}

int main() {
    int task;
    cout << "Выберите задание: 1 - сложение, 2 - производительность, 3 - дни в месяце: ";
    cin >> task;
    switch (task) {
        case 1: {
            int a, b;
            cin >> a >> b;
            cout << addNoCarry(a, b) << endl;
            break;
        }
        case 2: {
            long long h, k;
            cin >> h >> k;
            cout << products(h, k) << endl;
            break;
        }
        case 3: {
            int m, y;
            cin >> m >> y;
            int d = daysInMonth(m, y);
            if (d == 0) cout << "Неверный номер месяца" << endl;
            else cout << d << endl;
            break;
        }
        default:
            cout << "Нет такого задания" << endl;
    }
    return 0;
}
