// Класс-хранилище: объекты в обычном массиве, размерность задана константой
#ifndef STORAGE_H
#define STORAGE_H

#include "Persons.h"

const int MAX_PERSONS = 50;

class Storage {
private:
    Person* items[MAX_PERSONS];
    int count;

public:
    Storage();
    ~Storage();

    bool add(Person* p);                          // добавление
    bool edit(int index);                         // редактирование
    bool remove(int index);                       // удаление
    void showOne(int index) const;                // показать один объект
    void showAll() const;                         // показать все
    int find(const std::string& text) const;      // поиск по критерию (показывает найденные, возвращает число)
    int size() const;
};

#endif
