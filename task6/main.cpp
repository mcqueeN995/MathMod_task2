#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

struct Patient {
    string surname;
    string name;
    string birth_date;
    string phone;
    string address;
    string card_number;
    string blood_type;

    Patient() = default;
    Patient(const string& s, const string& n, const string& bd, 
            const string& p, const string& a, const string& cn, const string& bt)
        : surname(s), name(n), birth_date(bd), phone(p), 
          address(a), card_number(cn), blood_type(bt) {}
};

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
protected:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    virtual ~LinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    virtual void push(const T& val) = 0;
    virtual T pop() = 0;


    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }
    int getSize() const { return size; }
    void setHead(Node<T>* newHead) { head = newHead; }
    void setTail(Node<T>* newTail) { tail = newTail; }
    void incrementSize() { size++; }
    void decrementSize() { size--; }
};

template <typename T>
class Stack : virtual public LinkedList<T> {
public:
    void push(const T& val) override {
        Node<T>* newNode = new Node<T>(val);
        if (!this->getHead()) {
            this->setHead(newNode);
            this->setTail(newNode);
        } else {
            this->getTail()->next = newNode;
            this->setTail(newNode);
        }
        this->incrementSize();
    }

    T pop() override {
        if (!this->getHead()) throw runtime_error("Stack is empty");

        T val = this->getTail()->data;
        if (this->getHead() == this->getTail()) {
            delete this->getHead();
            this->setHead(nullptr);
            this->setTail(nullptr);
        } else {
            Node<T>* current = this->getHead();
            while (current->next != this->getTail()) current = current->next;
            delete this->getTail();
            this->setTail(current);
            current->next = nullptr;
        }
        this->decrementSize();
        return val;
    }
};

template <typename T>
class Queue : virtual public LinkedList<T> {
public:
    void push(const T& val) override {
        Node<T>* newNode = new Node<T>(val);
        if (!this->getHead()) {
            this->setHead(newNode);
            this->setTail(newNode);
        } else {
            this->getTail()->next = newNode;
            this->setTail(newNode);
        }
        this->incrementSize();
    }

    T pop() override {
        if (!this->getHead()) throw runtime_error("Queue is empty");

        T val = this->getHead()->data;
        Node<T>* temp = this->getHead();
        this->setHead(this->getHead()->next);
        delete temp;
        this->decrementSize();
        return val;
    }
};

template <typename T>
class StackQueue : protected Stack<T>, protected Queue<T> {
public:
    using Stack<T>::push;
    using Queue<T>::pop;
    using LinkedList<T>::operator[];

    void push(const T& val) override {
        Stack<T>::push(val);
    }

    T pop() override {
        return Queue<T>::pop();
    }


    int size() const { return this->getSize(); }
};

int main() {
    Patient p1("Иванов", "Иван", "01.01.1990", "1234567", "ул. Пушкина", "A123", "II+");
    Patient p2("Петров", "Пётр", "15.05.1985", "7654321", "ул. Лермонтова", "B456", "I-");

    StackQueue<Patient> sq;
    sq.push(p1);
    sq.push(p2);


    auto findPatient = [&](const string& surname) {
        for (int i = 0; i < sq.size(); ++i) {
            if (sq[i].surname == surname) return true;
        }
        return false;
    };

    cout << "Найден Иванов: " << (findPatient("Иванов") ? "Да" : "Нет") << endl;


    auto bloodFilter = [&](const string& blood) {
        StackQueue<Patient> result;
        for (int i = 0; i < sq.size(); ++i) {
            if (sq[i].blood_type == blood) result.push(sq[i]);
        }
        return result;
    };

    auto filtered = bloodFilter("II+");
    if (filtered.size() > 0) {
        cout << "Найдено пациентов с II+: " << filtered[0].surname << endl;
    } else {
        cout << "Пациентов с II+ не найдено" << endl;
    }

    return 0;
}