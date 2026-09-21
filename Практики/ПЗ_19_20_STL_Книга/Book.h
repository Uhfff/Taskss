// ПЗ 19_20, задание 5.1. Класс «Книга» (модуль Book.h + Book.cpp)
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:                                   // все поля закрытые
    std::string title;
    std::string author;
    int year;
    std::string category;

public:
    Book();
    Book(const std::string& title, const std::string& author, int year, const std::string& category);
    Book(const Book& other);               // конструктор копирования

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getCategory() const;
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    void setYear(int y);
    void setCategory(const std::string& c);

    Book& operator=(const Book& other);
    bool operator<(const Book& other) const;      // сравнение по названию
    bool operator>(const Book& other) const;
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;

    // ввод/вывод (одинаково работают для консоли и файлов)
    friend std::istream& operator>>(std::istream& in, Book& b);
    friend std::ostream& operator<<(std::ostream& out, const Book& b);
};

// функция сравнения для сортировки по убыванию (вторая версия sort)
bool compDesc(const Book& a, const Book& b);

#endif
