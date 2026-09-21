// Класс «Студенческая группа» (отдельный модуль: Group.h + Group.cpp)
#ifndef GROUP_H
#define GROUP_H

#include "Student.h"

class Group {
private:
    static const int MAX = 50;
    std::string name;             // название группы
    Student students[MAX];        // массив студентов
    int count;

public:
    Group(const std::string& name = "");

    void setName(const std::string& n);
    std::string getName() const;
    int size() const;

    void addStudent(const Student& s);
    void showExcellent() const;   // фамилии и группа студентов со средним баллом > 4.0
    void sortByBirthPlace();      // сортировка «пузырьком» по месту рождения
    void print() const;
};

#endif
