#include "Book.h"
using namespace std;

Book::Book() : title(""), author(""), year(0), category("") {}
Book::Book(const string& title, const string& author, int year, const string& category)
    : title(title), author(author), year(year), category(category) {}
Book::Book(const Book& o) : title(o.title), author(o.author), year(o.year), category(o.category) {}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
string Book::getCategory() const { return category; }
void Book::setTitle(const string& t) { title = t; }
void Book::setAuthor(const string& a) { author = a; }
void Book::setYear(int y) { year = y; }
void Book::setCategory(const string& c) { category = c; }

Book& Book::operator=(const Book& o) {
    if (this != &o) {
        title = o.title;
        author = o.author;
        year = o.year;
        category = o.category;
    }
    return *this;
}

bool Book::operator<(const Book& o) const { return title < o.title; }
bool Book::operator>(const Book& o) const { return title > o.title; }
bool Book::operator==(const Book& o) const {
    return title == o.title && author == o.author && year == o.year && category == o.category;
}
bool Book::operator!=(const Book& o) const { return !(*this == o); }

// формат: каждое поле на отдельной строке
istream& operator>>(istream& in, Book& b) {
    getline(in, b.title);
    getline(in, b.author);
    string y;
    getline(in, y);
    try { b.year = stoi(y); } catch (...) { b.year = 0; }
    getline(in, b.category);
    return in;
}

ostream& operator<<(ostream& out, const Book& b) {
    out << b.title << "\n" << b.author << "\n" << b.year << "\n" << b.category << "\n";
    return out;
}

bool compDesc(const Book& a, const Book& b) { return a > b; }
