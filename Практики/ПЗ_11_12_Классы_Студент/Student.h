// ПЗ 11_12, задание 5.1. Класс «Студент» (отдельный модуль: Student.h + Student.cpp)
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    std::string fio;          // фамилия и инициалы
    std::string birthPlace;   // место рождения
    int marks[5];             // успеваемость (пять оценок)

public:
    Student();
    Student(const std::string& fio, const std::string& birthPlace, const int marks[5]);

    std::string getFio() const;
    std::string getBirthPlace() const;
    double average() const;                       // средний балл

    void input();                                 // ввод с клавиатуры
    void print() const;

    // сравнение студентов по месту рождения
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
};

#endif
