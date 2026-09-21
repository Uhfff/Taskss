// ПЗ 13_14_15, вариант 2: Персона -> Студент, Преподаватель -> Заведующий кафедрой
// Модуль иерархии классов (Persons.h + Persons.cpp)
#ifndef PERSONS_H
#define PERSONS_H

#include <string>
#include <iostream>

// Абстрактный родительский класс (есть чисто виртуальные методы)
class Person {
private:                                   // все поля закрытые
    std::string name;
    int age;

public:
    Person(const std::string& name, int age);
    virtual ~Person();

    // свойства с проверкой значений (исключение при неверном вводе)
    std::string getName() const;
    int getAge() const;
    void setName(const std::string& n);
    void setAge(int a);

    // виртуальные методы
    virtual void show() const = 0;                          // вывод информации
    virtual std::string role() const = 0;                   // название роли
    virtual void input();                                   // ввод/редактирование данных
    virtual bool match(const std::string& text) const;      // поиск по критерию
};

class Student : public Person {
private:
    int course;
    double averageMark;

public:
    Student(const std::string& name, int age, int course, double averageMark);
    ~Student();
    int getCourse() const;
    double getAverageMark() const;
    void setCourse(int c);
    void setAverageMark(double m);

    void show() const override;
    std::string role() const override;
    void input() override;
    bool match(const std::string& text) const override;
};

class Teacher : public Person {
private:
    std::string subject;
    int experience;                        // стаж, лет

public:
    Teacher(const std::string& name, int age, const std::string& subject, int experience);
    ~Teacher();
    std::string getSubject() const;
    int getExperience() const;
    void setSubject(const std::string& s);
    void setExperience(int e);

    void show() const override;
    std::string role() const override;
    void input() override;
    bool match(const std::string& text) const override;
};

class HeadOfDepartment : public Teacher {
private:
    std::string department;

public:
    HeadOfDepartment(const std::string& name, int age, const std::string& subject,
                     int experience, const std::string& department);
    ~HeadOfDepartment();
    std::string getDepartment() const;
    void setDepartment(const std::string& d);

    void show() const override;
    std::string role() const override;
    void input() override;
    bool match(const std::string& text) const override;
};

#endif
