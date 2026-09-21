// ПЗ 19_20, задание 5.1 «Книга». Контейнер STL list, шаблон класса, меню.
// Сборка: g++ main.cpp Book.cpp -o books
// Данные загружаются из books.txt при старте и сохраняются в него при выходе.
#include <iostream>
#include <fstream>
#include "Book.h"
#include "Collection.h"
using namespace std;

Book inputBookFromConsole() {
    Book b;
    string s;
    int y;
    cout << "Название: ";
    getline(cin, s);
    b.setTitle(s);
    cout << "Автор: ";
    getline(cin, s);
    b.setAuthor(s);
    cout << "Год издания: ";
    cin >> y;
    cin.ignore(1000, '\n');
    b.setYear(y);
    cout << "Категория: ";
    getline(cin, s);
    b.setCategory(s);
    return b;
}

int main() {
    Collection<Book> books;

    ifstream fin("books.txt");                            // загрузка объектов из потока
    if (fin.is_open()) books.load(fin);
    fin.close();

    int choice;
    do {
        cout << "\n===== МЕНЮ =====\n"
                "1. Добавить книгу\n"
                "2. Редактировать книгу\n"
                "3. Удалить книгу\n"
                "4. Показать все книги\n"
                "5. Поиск (по автору)\n"
                "6. Сортировка по убыванию (по названию)\n"
                "0. Выход (с сохранением в файл)\n"
                "Выбор: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        if (choice == 1) {
            books.insert(inputBookFromConsole());
        } else if (choice == 2) {
            int n;
            cout << "Номер книги: ";
            cin >> n;
            cin.ignore(1000, '\n');
            if (n < 1 || n > books.size()) cout << "Нет книги с таким номером" << endl;
            else {
                cout << "Новые данные:" << endl;
                books.edit(n, inputBookFromConsole());
            }
        } else if (choice == 3) {
            int n;
            cout << "Номер книги: ";
            cin >> n;
            cin.ignore(1000, '\n');
            if (!books.remove(n)) cout << "Нет книги с таким номером" << endl;
        } else if (choice == 4) {
            books.show();
        } else if (choice == 5) {
            string author;
            cout << "Автор: ";
            getline(cin, author);
            vector<Book> found = books.findAll([&author](const Book& b) {
                return b.getAuthor().find(author) != string::npos;
            });
            if (found.empty()) cout << "Ничего не найдено" << endl;
            for (const Book& b : found) cout << b << "---" << endl;
        } else if (choice == 6) {
            books.sortBy(compDesc);
            cout << "Отсортировано по убыванию" << endl;
            books.show();
        }
    } while (choice != 0);

    ofstream fout("books.txt");                           // запись объектов в поток
    books.save(fout);
    return 0;
}
