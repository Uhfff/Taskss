#include "Persons.h"
#include <stdexcept>
using namespace std;

// ---------- Person ----------
Person::Person(const string& name, int age) : name(""), age(0) {
    setName(name);
    setAge(age);
}
Person::~Person() {}

string Person::getName() const { return name; }
int Person::getAge() const { return age; }

void Person::setName(const string& n) {
    if (n.empty()) throw invalid_argument("Имя не может быть пустым");
    name = n;
}
void Person::setAge(int a) {
    if (a < 0 || a > 120) throw invalid_argument("Возраст должен быть от 0 до 120");
    age = a;
}

void Person::input() {
    string n;
    int a;
    cout << "Имя: ";
    getline(cin, n);
    cout << "Возраст: ";
    cin >> a;
    cin.ignore(1000, '\n');
    setName(n);
    setAge(a);
}

bool Person::match(const string& text) const {
    return name.find(text) != string::npos;
}

// ---------- Student ----------
Student::Student(const string& name, int age, int course, double averageMark)
    : Person(name, age), course(1), averageMark(0) {
    setCourse(course);
    setAverageMark(averageMark);
}
Student::~Student() {}

int Student::getCourse() const { return course; }
double Student::getAverageMark() const { return averageMark; }
void Student::setCourse(int c) {
    if (c < 1 || c > 6) throw invalid_argument("Курс должен быть от 1 до 6");
    course = c;
}
void Student::setAverageMark(double m) {
    if (m < 0 || m > 5) throw invalid_argument("Средний балл должен быть от 0 до 5");
    averageMark = m;
}

void Student::show() const {
    cout << "[" << role() << "] " << getName() << ", " << getAge() << " лет, курс "
         << course << ", средний балл " << averageMark << endl;
}
string Student::role() const { return "Студент"; }

void Student::input() {
    Person::input();
    int c;
    double m;
    cout << "Курс: ";
    cin >> c;
    cout << "Средний балл: ";
    cin >> m;
    cin.ignore(1000, '\n');
    setCourse(c);
    setAverageMark(m);
}
bool Student::match(const string& text) const {
    return Person::match(text) || to_string(course) == text;
}

// ---------- Teacher ----------
Teacher::Teacher(const string& name, int age, const string& subject, int experience)
    : Person(name, age), subject(subject), experience(0) {
    setExperience(experience);
}
Teacher::~Teacher() {}

string Teacher::getSubject() const { return subject; }
int Teacher::getExperience() const { return experience; }
void Teacher::setSubject(const string& s) { subject = s; }
void Teacher::setExperience(int e) {
    if (e < 0 || e > getAge()) throw invalid_argument("Некорректный стаж");
    experience = e;
}

void Teacher::show() const {
    cout << "[" << role() << "] " << getName() << ", " << getAge() << " лет, предмет: "
         << subject << ", стаж " << experience << " лет" << endl;
}
string Teacher::role() const { return "Преподаватель"; }

void Teacher::input() {
    Person::input();
    string s;
    int e;
    cout << "Предмет: ";
    getline(cin, s);
    cout << "Стаж (лет): ";
    cin >> e;
    cin.ignore(1000, '\n');
    setSubject(s);
    setExperience(e);
}
bool Teacher::match(const string& text) const {
    return Person::match(text) || subject.find(text) != string::npos;
}

// ---------- HeadOfDepartment ----------
HeadOfDepartment::HeadOfDepartment(const string& name, int age, const string& subject,
                                   int experience, const string& department)
    : Teacher(name, age, subject, experience), department(department) {}
HeadOfDepartment::~HeadOfDepartment() {}

string HeadOfDepartment::getDepartment() const { return department; }
void HeadOfDepartment::setDepartment(const string& d) { department = d; }

void HeadOfDepartment::show() const {
    cout << "[" << role() << "] " << getName() << ", " << getAge() << " лет, предмет: "
         << getSubject() << ", стаж " << getExperience() << " лет, кафедра: " << department << endl;
}
string HeadOfDepartment::role() const { return "Заведующий кафедрой"; }

void HeadOfDepartment::input() {
    Teacher::input();
    cout << "Кафедра: ";
    getline(cin, department);
}
bool HeadOfDepartment::match(const string& text) const {
    return Teacher::match(text) || department.find(text) != string::npos;
}
