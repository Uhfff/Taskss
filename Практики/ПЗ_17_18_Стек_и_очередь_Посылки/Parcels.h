// Запись «Посылка» и функции работы с очередью посылок (модуль Parcels.h + Parcels.cpp)
#ifndef PARCELS_H
#define PARCELS_H

#include <string>
#include "Lists.h"

struct Parcel {
    int number;               // номер посылки
    double weight;            // вес
    double price;             // цена
    int date[3];              // дата отправки: день, месяц, год
    std::string destination;  // пункт назначения

    Parcel() : number(0), weight(0), price(0), date{0, 0, 0} {}
};

// для группировки: пункт назначения и суммарная стоимость
struct DestinationTotal {
    std::string destination;
    double total;
    DestinationTotal() : total(0) {}
};

Parcel inputParcel();
void printParcel(const Parcel& p);

void addParcel(Queue<Parcel>& q);
bool editParcel(Queue<Parcel>& q, int number);
bool deleteParcel(Queue<Parcel>& q, int number);
void showParcels(const Queue<Parcel>& q);

// пункт 3: посылки, отправленные во втором квартале прошлого года
void showSecondQuarterLastYear(const Queue<Parcel>& q, int currentYear);

// пункт 4: общая стоимость посылок по каждому пункту назначения (группировка через стек)
void showTotalsByDestination(const Queue<Parcel>& q);

#endif
