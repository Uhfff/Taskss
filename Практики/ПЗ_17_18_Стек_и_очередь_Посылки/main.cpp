// ПЗ 17_18, задание 5.1 «Посылки». Хранение - очередь, группировка - стек.
// Сборка: g++ main.cpp Parcels.cpp -o parcels
#include <iostream>
#include <ctime>
#include "Parcels.h"
using namespace std;

int main() {
    Queue<Parcel> parcels;
    time_t t = time(nullptr);
    int currentYear = localtime(&t)->tm_year + 1900;

    int choice;
    do {
        cout << "\n===== МЕНЮ =====\n"
                "1. Добавить посылку\n"
                "2. Редактировать посылку\n"
                "3. Удалить посылку\n"
                "4. Показать все посылки\n"
                "5. Посылки, отправленные во втором квартале прошлого года\n"
                "6. Общая стоимость посылок по пунктам назначения\n"
                "0. Выход\n"
                "Выбор: ";
        cin >> choice;
        if (choice == 1) {
            addParcel(parcels);
        } else if (choice == 2) {
            int num;
            cout << "Номер посылки: ";
            cin >> num;
            if (!editParcel(parcels, num)) cout << "Такой посылки нет" << endl;
        } else if (choice == 3) {
            int num;
            cout << "Номер посылки: ";
            cin >> num;
            if (!deleteParcel(parcels, num)) cout << "Такой посылки нет" << endl;
        } else if (choice == 4) {
            showParcels(parcels);
        } else if (choice == 5) {
            showSecondQuarterLastYear(parcels, currentYear);
        } else if (choice == 6) {
            showTotalsByDestination(parcels);
        }
    } while (choice != 0);
    return 0;
}
