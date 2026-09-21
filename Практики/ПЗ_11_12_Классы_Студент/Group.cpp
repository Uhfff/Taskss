#include "Group.h"
using namespace std;

Group::Group(const string& name) : name(name), count(0) {}

void Group::setName(const string& n) { name = n; }
string Group::getName() const { return name; }
int Group::size() const { return count; }

void Group::addStudent(const Student& s) {
    if (count < MAX) students[count++] = s;
    else cout << "Группа заполнена" << endl;
}

void Group::showExcellent() const {
    bool found = false;
    for (int i = 0; i < count; i++)
        if (students[i].average() > 4.0) {
            cout << students[i].getFio() << " - группа " << name << endl;
            found = true;
        }
    if (!found) cout << "Студентов со средним баллом выше 4.0 нет" << endl;
}

void Group::sortByBirthPlace() {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (students[j] > students[j + 1]) {          // перегруженная операция сравнения
                Student t = students[j];
                students[j] = students[j + 1];
                students[j + 1] = t;
            }
}

void Group::print() const {
    cout << "Группа " << name << ":" << endl;
    for (int i = 0; i < count; i++) students[i].print();
}
