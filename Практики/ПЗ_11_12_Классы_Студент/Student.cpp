#include "Student.h"
using namespace std;

Student::Student() : fio(""), birthPlace("") {
    for (int i = 0; i < 5; i++) marks[i] = 0;
}

Student::Student(const string& fio, const string& birthPlace, const int m[5])
    : fio(fio), birthPlace(birthPlace) {
    for (int i = 0; i < 5; i++) marks[i] = m[i];
}

string Student::getFio() const { return fio; }
string Student::getBirthPlace() const { return birthPlace; }

double Student::average() const {
    double sum = 0;
    for (int i = 0; i < 5; i++) sum += marks[i];
    return sum / 5;
}

void Student::input() {
    cout << "Фамилия и инициалы: ";
    getline(cin, fio);
    cout << "Место рождения: ";
    getline(cin, birthPlace);
    cout << "Пять оценок через пробел: ";
    for (int i = 0; i < 5; i++) cin >> marks[i];
    cin.ignore(1000, '\n');
}

void Student::print() const {
    cout << fio << ", место рождения: " << birthPlace << ", оценки:";
    for (int i = 0; i < 5; i++) cout << " " << marks[i];
    cout << endl;
}

bool Student::operator<(const Student& other) const { return birthPlace < other.birthPlace; }
bool Student::operator>(const Student& other) const { return birthPlace > other.birthPlace; }
bool Student::operator==(const Student& other) const { return birthPlace == other.birthPlace; }
bool Student::operator!=(const Student& other) const { return !(*this == other); }
