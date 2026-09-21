// Шаблон класса-обёртки над контейнером STL list
#ifndef COLLECTION_H
#define COLLECTION_H

#include <list>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

template <class T>
class Collection {
private:
    std::list<T> items;

public:
    // вставка (в конец)
    void insert(const T& value) { items.push_back(value); }

    // удаление по номеру (с 1)
    bool remove(int index) {
        if (index < 1 || index > (int)items.size()) return false;
        auto it = items.begin();
        std::advance(it, index - 1);
        items.erase(it);
        return true;
    }

    // редактирование: замена элемента по номеру (с 1)
    bool edit(int index, const T& value) {
        if (index < 1 || index > (int)items.size()) return false;
        auto it = items.begin();
        std::advance(it, index - 1);
        *it = value;
        return true;
    }

    // просмотр
    void show(std::ostream& out = std::cout) const {
        if (items.empty()) { out << "Контейнер пуст" << std::endl; return; }
        int i = 1;
        for (const T& item : items) out << i++ << ".\n" << item;
    }

    // поиск по условию (find_if): возвращает найденные элементы
    template <class Pred>
    std::vector<T> findAll(Pred pred) const {
        std::vector<T> result;
        auto it = items.begin();
        while ((it = std::find_if(it, items.end(), pred)) != items.end()) {
            result.push_back(*it);
            ++it;
        }
        return result;
    }

    // сортировка по возрастанию (operator<)
    void sortAsc() { items.sort(); }

    // сортировка по убыванию: у list std::sort не работает (нет итераторов произвольного доступа),
    // поэтому используется одноимённый метод list::sort со своей функцией сравнения
    template <class Comp>
    void sortBy(Comp comp) { items.sort(comp); }

    int size() const { return (int)items.size(); }

    // загрузка из потока
    void load(std::istream& in) {
        T item;
        while (in >> item) {
            if (item == T()) break;            // пустая запись - конец данных
            items.push_back(item);
        }
    }

    // запись в поток
    void save(std::ostream& out) const {
        for (const T& item : items) out << item;
    }
};

#endif
