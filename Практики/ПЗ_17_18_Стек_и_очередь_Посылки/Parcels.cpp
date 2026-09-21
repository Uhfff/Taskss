#include "Parcels.h"
#include <iostream>
using namespace std;

Parcel inputParcel() {
    Parcel p;
    cout << "Номер посылки: ";
    cin >> p.number;
    cout << "Вес: ";
    cin >> p.weight;
    cout << "Цена: ";
    cin >> p.price;
    cout << "Дата отправки (день месяц год): ";
    cin >> p.date[0] >> p.date[1] >> p.date[2];
    cin.ignore(1000, '\n');
    cout << "Пункт назначения: ";
    getline(cin, p.destination);
    return p;
}

void printParcel(const Parcel& p) {
    cout << "№" << p.number << ", вес " << p.weight << ", цена " << p.price
         << ", дата " << p.date[0] << "." << p.date[1] << "." << p.date[2]
         << ", пункт назначения: " << p.destination << endl;
}

void addParcel(Queue<Parcel>& q) {
    q.enqueue(inputParcel());
}

bool editParcel(Queue<Parcel>& q, int number) {
    for (Node<Parcel>* n = q.first(); n != nullptr; n = n->next)
        if (n->data.number == number) {
            cout << "Введите новые данные:" << endl;
            n->data = inputParcel();
            return true;
        }
    return false;
}

bool deleteParcel(Queue<Parcel>& q, int number) {
    return q.removeIf([number](const Parcel& p) { return p.number == number; });
}

void showParcels(const Queue<Parcel>& q) {
    if (q.isEmpty()) { cout << "Очередь пуста" << endl; return; }
    for (Node<Parcel>* n = q.first(); n != nullptr; n = n->next) printParcel(n->data);
}

void showSecondQuarterLastYear(const Queue<Parcel>& q, int currentYear) {
    bool found = false;
    for (Node<Parcel>* n = q.first(); n != nullptr; n = n->next) {
        const Parcel& p = n->data;
        if (p.date[2] == currentYear - 1 && p.date[1] >= 4 && p.date[1] <= 6) {
            cout << "Посылка №" << p.number << " - " << p.destination << endl;
            found = true;
        }
    }
    if (!found) cout << "Посылок, отправленных во втором квартале прошлого года, нет" << endl;
}

void showTotalsByDestination(const Queue<Parcel>& q) {
    if (q.isEmpty()) { cout << "Очередь пуста" << endl; return; }
    Stack<DestinationTotal> groups;
    for (Node<Parcel>* n = q.first(); n != nullptr; n = n->next) {
        bool done = false;
        for (Node<DestinationTotal>* g = groups.top(); g != nullptr; g = g->next)   // ищем пункт в стеке
            if (g->data.destination == n->data.destination) {
                g->data.total += n->data.price;
                done = true;
                break;
            }
        if (!done) {
            DestinationTotal d;
            d.destination = n->data.destination;
            d.total = n->data.price;
            groups.push(d);
        }
    }
    DestinationTotal d;
    while (groups.pop(d))                                                              // выводим, снимая со стека
        cout << d.destination << ": " << d.total << endl;
}
