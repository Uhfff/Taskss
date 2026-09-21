// ПЗ 7_8. Строки, файлы, подпрограммы
// 5.1 (в аудитории): строки char[]; 5.2 (самостоятельно): строки string и файлы.
// Не решено: 5.2.5 (слияние JSON) - требует внешней JSON-библиотеки.
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

// ---------- 5.1.1 Цифры переносятся в конец строки, остальные символы в прежнем порядке ----------
void task511() {
    char s[256], letters[256], digits[256];
    cin.ignore();
    cin.getline(s, 256);
    int a = 0, b = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit((unsigned char)s[i])) digits[b++] = s[i];
        else letters[a++] = s[i];
    }
    letters[a] = '\0';
    digits[b] = '\0';
    strcat(letters, digits);
    cout << letters << endl;
}

// ---------- 5.1.2 Если строка начинается и оканчивается одним знаком, заменить его четвёртым символом ----------
void task512() {
    char s[256];
    cin.ignore();
    cin.getline(s, 256);
    int len = strlen(s);
    if (len >= 4 && s[0] == s[len - 1]) {
        char first = s[0], fourth = s[3];
        for (int i = 0; i < len; i++)
            if (s[i] == first) s[i] = fourth;
    }
    cout << s << endl;
}

// ---------- 5.1.3 Слова в обратном порядке (слова разделены одним или несколькими пробелами) ----------
void task513() {
    char s[256];
    cin.ignore();
    cin.getline(s, 256);
    char* words[128];
    int cnt = 0;
    char* w = strtok(s, " ");
    while (w != nullptr) {
        words[cnt++] = w;
        w = strtok(nullptr, " ");
    }
    for (int i = cnt - 1; i >= 0; i--) {
        cout << words[i];
        if (i > 0) cout << " ";
    }
    cout << endl;
}

// ---------- 5.1.4 Сжатие: самая длинная подстрока, повторяющаяся без наложения, заменяется кодом '#' ----------
void task514() {
    char s[256];
    cin.ignore();
    cin.getline(s, 256);
    int n = strlen(s);
    int bestLen = 0, bestPos = 0;
    for (int len = n / 2; len >= 1 && bestLen == 0; len--) {          // длину перебираем от большей к меньшей
        for (int i = 0; i + len <= n && bestLen == 0; i++)
            for (int j = i + len; j + len <= n; j++)
                if (strncmp(s + i, s + j, len) == 0) { bestLen = len; bestPos = i; break; }
    }
    if (bestLen == 0) { cout << s << endl; return; }

    char pattern[256];
    strncpy(pattern, s + bestPos, bestLen);
    pattern[bestLen] = '\0';
    char result[256];
    int r = 0;
    for (int i = 0; i < n;) {
        if (i + bestLen <= n && strncmp(s + i, pattern, bestLen) == 0) {
            result[r++] = '#';
            i += bestLen;
        } else {
            result[r++] = s[i++];
        }
    }
    result[r] = '\0';
    cout << "Код # = \"" << pattern << "\"" << endl;
    cout << result << endl;
}

// ---------- 5.1.5 Первое слово, символы которого идут в строгом порядке возрастания кодов ----------
void task515() {
    char s[256];
    cin.ignore();
    cin.getline(s, 256);
    char* w = strtok(s, " ");
    while (w != nullptr) {
        bool ok = true;
        for (int i = 1; w[i] != '\0'; i++)
            if ((unsigned char)w[i] <= (unsigned char)w[i - 1]) { ok = false; break; }
        if (ok) { cout << w << endl; return; }
        w = strtok(nullptr, " ");
    }
    cout << "Такого слова нет" << endl;
}

// ---------- 5.2.1 Поиск данных ----------
string toLower(string s) {
    for (size_t i = 0; i < s.size(); i++) s[i] = tolower((unsigned char)s[i]);
    return s;
}

void searchTitles(const string& inName, const string& outName) {
    ifstream fin(inName);
    ofstream fout(outName);
    if (!fin.is_open()) { cout << "Файл не открыт" << endl; return; }
    string line, titles[1000];
    int cnt = 0;
    while (getline(fin, line)) titles[cnt++] = line;
    if (cnt == 0) return;
    string query = toLower(titles[cnt - 1]);          // последняя строка - запрос
    for (int i = 0; i < cnt - 1; i++)
        if (toLower(titles[i]).find(query) != string::npos)
            fout << titles[i] << endl;
}

void task521() { searchTitles("input.txt", "output.txt"); }

// ---------- 5.2.2 Файловая статистика 1 (каждый параметр - отдельная функция) ----------
int countAll(const string& f) { ifstream in(f); double x; int c = 0; while (in >> x) c++; return c; }
int countPositive(const string& f) { ifstream in(f); double x; int c = 0; while (in >> x) if (x > 0) c++; return c; }
double minValue(const string& f) { ifstream in(f); double x, m = 1e300; while (in >> x) if (x < m) m = x; return m; }
double maxValue(const string& f) { ifstream in(f); double x, m = -1e300; while (in >> x) if (x > m) m = x; return m; }
double sumValues(const string& f) { ifstream in(f); double x, s = 0; while (in >> x) s += x; return s; }
double average(const string& f) { int c = countAll(f); return c == 0 ? 0 : sumValues(f) / c; }

void task522() {
    string name;
    cin >> name;
    ifstream test(name);
    if (!test.is_open()) { cout << "Файл не открыт" << endl; return; }
    cout << countAll(name) << endl;
    cout << countPositive(name) << endl;
    cout << minValue(name) << endl;
    cout << maxValue(name) << endl;
    cout << sumValues(name) << endl;
    cout << fixed << setprecision(2) << average(name) << endl;
}

// ---------- 5.2.3 Файловая статистика 2 (английский текст) ----------
// разбор файла на слова (последовательности букв)
int splitWords(const string& f, string words[], int maxWords) {
    ifstream in(f);
    string word, line;
    int cnt = 0;
    while (getline(in, line)) {
        word = "";
        for (size_t i = 0; i <= line.size(); i++) {
            if (i < line.size() && isalpha((unsigned char)line[i])) word += line[i];
            else if (!word.empty()) {
                if (cnt < maxWords) words[cnt++] = word;
                word = "";
            }
        }
    }
    return cnt;
}

bool isVowel(char c) { return string("aeiouAEIOU").find(c) != string::npos; }

int countVowels(const string& f) {
    ifstream in(f); char c; int r = 0;
    while (in.get(c)) if (isalpha((unsigned char)c) && isVowel(c)) r++;
    return r;
}
int countConsonants(const string& f) {
    ifstream in(f); char c; int r = 0;
    while (in.get(c)) if (isalpha((unsigned char)c) && !isVowel(c)) r++;
    return r;
}
int countCapitalWords(const string& f) {
    static string w[5000];
    int n = splitWords(f, w, 5000), r = 0;
    for (int i = 0; i < n; i++) if (isupper((unsigned char)w[i][0])) r++;
    return r;
}
int countLongestWords(const string& f) {
    static string w[5000];
    int n = splitWords(f, w, 5000), mx = 0, r = 0;
    for (int i = 0; i < n; i++) mx = max(mx, (int)w[i].size());
    for (int i = 0; i < n; i++) if ((int)w[i].size() == mx) r++;
    return r;
}
int countPalindromes(const string& f) {
    static string w[5000];
    int n = splitWords(f, w, 5000), r = 0;
    for (int i = 0; i < n; i++) {
        string s = toLower(w[i]);
        string rev(s.rbegin(), s.rend());
        if (s.size() > 1 && s == rev) r++;              // однобуквенные слова палиндромами не считаем
    }
    return r;
}

void task523() {
    string name;
    cin >> name;
    ifstream test(name);
    if (!test.is_open()) { cout << "Файл не открыт" << endl; return; }
    cout << "количество гласных: " << countVowels(name) << endl;
    cout << "количество согласных: " << countConsonants(name) << endl;
    cout << "количество слов, начинающиеся с заглавной буквы: " << countCapitalWords(name) << endl;
    cout << "количество слов максимальной длины: " << countLongestWords(name) << endl;
    int p = countPalindromes(name);
    if (p == 0) cout << "нет слов, являющихся палиндромом" << endl;
    else cout << "количество слов-палиндромов: " << p << endl;
}

// ---------- 5.2.4 Файловая разница ----------
set<string> readWords(const string& name) {
    set<string> res;
    ifstream in(name);
    string w;
    while (in >> w) res.insert(w);
    return res;
}

void fileDifference(const string& f1, const string& f2, const string& out) {
    set<string> a = readWords(f1), b = readWords(f2);
    ofstream fout(out);
    set<string> result;                                 // set сам упорядочит слова и уберёт повторы
    for (const string& w : a) if (!b.count(w)) result.insert(w);
    for (const string& w : b) if (!a.count(w)) result.insert(w);
    for (const string& w : result) fout << w << endl;
}

void task524() {
    string f1, f2, f3;
    cin >> f1 >> f2 >> f3;
    fileDifference(f1, f2, f3);
}

int main() {
    int task;
    cout << "Задание: 1-5 (5.1.x, char[]), 6-9 (5.2.1-5.2.4, string и файлы): ";
    cin >> task;
    switch (task) {
        case 1: task511(); break;
        case 2: task512(); break;
        case 3: task513(); break;
        case 4: task514(); break;
        case 5: task515(); break;
        case 6: task521(); break;
        case 7: task522(); break;
        case 8: task523(); break;
        case 9: task524(); break;
        default: cout << "Нет такого задания" << endl;
    }
    return 0;
}
