// ПЗ 17_18. Собственные реализации очереди и стека на односвязном линейном списке
// (библиотечные stack/queue не используются)
#ifndef LISTS_H
#define LISTS_H

template <class T>
struct Node {
    T data;
    Node<T>* next;
};

// ---------------- ОЧЕРЕДЬ (FIFO) ----------------
template <class T>
class Queue {
private:
    Node<T>* head;      // откуда извлекаем
    Node<T>* tail;      // куда добавляем
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    ~Queue() { clear(); }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }
    Node<T>* first() const { return head; }          // для обхода списка

    void enqueue(const T& value) {
        Node<T>* n = new Node<T>{ value, nullptr };
        if (tail == nullptr) head = tail = n;
        else { tail->next = n; tail = n; }
        count++;
    }

    bool dequeue(T& value) {
        if (head == nullptr) return false;
        Node<T>* t = head;
        value = t->data;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete t;
        count--;
        return true;
    }

    void clear() {
        T tmp;
        while (dequeue(tmp)) {}
    }

    // удаление элемента по условию: очередь «прокручивается» целиком
    template <class Pred>
    bool removeIf(Pred pred) {
        bool removed = false;
        int n = count;
        for (int i = 0; i < n; i++) {
            T v;
            dequeue(v);
            if (!removed && pred(v)) removed = true;     // пропускаем один найденный элемент
            else enqueue(v);
        }
        return removed;
    }
};

// ---------------- СТЕК (LIFO) ----------------
template <class T>
class Stack {
private:
    Node<T>* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}
    ~Stack() { clear(); }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }
    Node<T>* top() const { return topNode; }         // для обхода списка

    void push(const T& value) {
        topNode = new Node<T>{ value, topNode };
        count++;
    }

    bool pop(T& value) {
        if (topNode == nullptr) return false;
        Node<T>* t = topNode;
        value = t->data;
        topNode = topNode->next;
        delete t;
        count--;
        return true;
    }

    void clear() {
        T tmp;
        while (pop(tmp)) {}
    }
};

#endif
