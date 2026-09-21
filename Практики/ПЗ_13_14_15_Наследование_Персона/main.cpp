// ПЗ 13_14_15. Меню работы с иерархией классов
// Сборка: g++ main.cpp Persons.cpp Storage.cpp -o persons
#include <iostream>
#include <stdexcept>
#include "Storage.h"
using namespace std;

Person* createPerson(int type) {
    switch (type) {
        case 1: return new Student("Новый студент", 18, 1, 0);
        case 2: return new Teacher("Новый преподаватель", 30, "Предмет", 0);
        case 3: return new HeadOfDepartment("Новый заведующий", 40, "Предмет", 0, "Кафедра");
        default: return nullptr;
    }
}

int main() {
    Storage storage;
    int choice;
    do {
        cout << "\n===== МЕНЮ =====\n"
                "1. Добавить объект\n"
                "2. Редактировать объект\n"
                "3. Удалить объект\n"
                "4. Показать объект по номеру\n"
                "5. Показать все объекты\n"
                "6. Поиск (по имени, курсу, предмету, кафедре)\n"
                "0. Выход\n"
                "Выбор: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        try {
            if (choice == 1) {
                int type;
                cout << "1 - студент, 2 - преподаватель, 3 - заведующий кафедрой: ";
                cin >> type;
                cin.ignore(1000, '\n');
                Person* p = createPerson(type);
                if (!p) { cout << "Неверный тип" << endl; continue; }
                try {
                    p->input();                                    // при ошибке ввода - исключение
                } catch (...) {
                    delete p;
                    throw;
                }
                if (!storage.add(p)) { delete p; cout << "Хранилище заполнено" << endl; }
            } else if (choice == 2) {
                int idx;
                cout << "Номер: ";
                cin >> idx;
                cin.ignore(1000, '\n');
                if (!storage.edit(idx - 1)) cout << "Нет объекта с таким номером" << endl;
            } else if (choice == 3) {
                int idx;
                cout << "Номер: ";
                cin >> idx;
                cin.ignore(1000, '\n');
                if (!storage.remove(idx - 1)) cout << "Нет объекта с таким номером" << endl;
            } else if (choice == 4) {
                int idx;
                cout << "Номер: ";
                cin >> idx;
                cin.ignore(1000, '\n');
                storage.showOne(idx - 1);
            } else if (choice == 5) {
                storage.showAll();
            } else if (choice == 6) {
                string text;
                cout << "Что искать: ";
                getline(cin, text);
                if (storage.find(text) == 0) cout << "Ничего не найдено" << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "Ошибка ввода: " << e.what() << endl;
        }
    } while (choice != 0);
    return 0;
}
