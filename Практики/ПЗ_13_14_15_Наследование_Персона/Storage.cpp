#include "Storage.h"
#include <stdexcept>
using namespace std;

Storage::Storage() : count(0) {}

Storage::~Storage() {
    for (int i = 0; i < count; i++) delete items[i];      // виртуальный деструктор - удалится верный класс
}

bool Storage::add(Person* p) {
    if (count >= MAX_PERSONS) return false;
    items[count++] = p;
    return true;
}

bool Storage::edit(int index) {
    if (index < 0 || index >= count) return false;
    items[index]->input();                                // виртуальный вызов
    return true;
}

bool Storage::remove(int index) {
    if (index < 0 || index >= count) return false;
    delete items[index];
    for (int i = index; i < count - 1; i++) items[i] = items[i + 1];
    count--;
    return true;
}

void Storage::showOne(int index) const {
    if (index < 0 || index >= count) { cout << "Нет объекта с таким номером" << endl; return; }
    items[index]->show();
}

void Storage::showAll() const {
    if (count == 0) { cout << "Список пуст" << endl; return; }
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        items[i]->show();                                 // полиморфизм
    }
}

int Storage::find(const string& text) const {
    int found = 0;
    for (int i = 0; i < count; i++)
        if (items[i]->match(text)) {
            cout << i + 1 << ". ";
            items[i]->show();
            found++;
        }
    return found;
}

int Storage::size() const { return count; }
