// ПЗ 11_12, задание 5.1 «Студент». Сборка: g++ main.cpp Student.cpp Group.cpp -o student
#include <iostream>
#include "Group.h"
using namespace std;

int main() {
    string groupName;
    cout << "Название группы: ";
    getline(cin, groupName);
    Group group(groupName);

    int n;
    cout << "Сколько студентов ввести: ";
    cin >> n;
    cin.ignore(1000, '\n');
    for (int i = 0; i < n; i++) {
        cout << "--- Студент " << i + 1 << " ---" << endl;
        Student s;
        s.input();
        group.addStudent(s);
    }

    cout << "\nСтуденты со средним баллом больше 4.0:" << endl;
    group.showExcellent();

    group.sortByBirthPlace();
    cout << "\nСписок, отсортированный по месту рождения:" << endl;
    group.print();
    return 0;
}
