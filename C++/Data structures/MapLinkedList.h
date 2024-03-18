#include <iostream>

using KeyType = int;
using ValueType = double;

// Класс для представления узла списка
class Node {
public:
    KeyType key;
    ValueType value;
    Node* next;

    Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

// Класс для представления связного списка
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void insert(KeyType key, ValueType value);
    bool find(KeyType key, ValueType& value) const;
    void remove(KeyType key);

private:
    Node* head;
};

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::insert(KeyType key, ValueType value) {
    Node* newNode = new Node(key, value);
    newNode->next = head;
    head = newNode;
}

bool LinkedList::find(KeyType key, ValueType& value) const {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

void LinkedList::remove(KeyType key) {
    Node* current = head;
    Node* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
                delete current;
            } else {
                // Удаляем первый элемент
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            return;
        }

        prev = current;
        current = current->next;
    }
}

// Класс отображения на связном списке
class MapLinkedList {
public:
    MapLinkedList(); // Конструктор
    void MAKENULL(); // Делает отображение пустым.
    void ASSIGN(KeyType d, ValueType r); // Делает M(d) равным r.
    bool COMPUTE(KeyType d, ValueType& r); // Возвращает true и присваивает r значение M(d), если M(d) определено.

private:
    LinkedList linkedList;
};

MapLinkedList::MapLinkedList() {}

void MapLinkedList::MAKENULL() {
    linkedList.~LinkedList();
}

void MapLinkedList::ASSIGN(KeyType d, ValueType r) {
    linkedList.insert(d, r);
}

bool MapLinkedList::COMPUTE(KeyType d, ValueType& r) {
    return linkedList.find(d, r);
}
