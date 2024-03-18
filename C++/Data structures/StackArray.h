// Package: StackArray
#include <iostream>

// Замените ElementType на фактический тип вашего элемента
using ElementType = int;

class StackArray {
public:
    StackArray(); // Конструктор
    void MAKENULL(); // Очищает стек, делая его пустым.
    ElementType TOP(); // Возвращает элемент из вершины стека.
    ElementType POP(); // Удаляет элемент из вершины стека и возвращает его.
    void PUSH(ElementType x); // Вставляет элемент x в вершину стека.
    bool EMPTY(); // Возвращает true, если стек пуст, и false в противном случае.
    bool FULL(); // Возвращает true, если стек полон, и false в противном случае.

private:
    static const int MAX_SIZE = 100; // Задайте максимальный размер стека
    ElementType stack[MAX_SIZE]; // Массив для хранения элементов стека
    int top; // Индекс вершины стека

};

// Определение методов класса StackArray
StackArray::StackArray() {
    MAKENULL();
}

void StackArray::MAKENULL() {
    top = -1; // Устанавливаем вершину стека в -1, делая стек пустым
}

ElementType StackArray::TOP() {
    if (!EMPTY()) {
        return stack[top]; // Возвращаем элемент из вершины стека
    } else {
        std::cerr << "Error: Stack is empty." << std::endl;
        return 0;
    }
}

ElementType StackArray::POP() {
    if (!EMPTY()) {
        return stack[top--]; // Удаляем элемент из вершины стека и возвращаем его
    } else {
        std::cerr << "Error: Stack is empty." << std::endl;
        return 0;
    }
}

void StackArray::PUSH(ElementType x) {
    if (!FULL()) {
        stack[++top] = x; // Увеличиваем индекс вершины и добавляем элемент в стек
    } else {
        std::cerr << "Error: Stack is full." << std::endl;
        return;
    }
}

bool StackArray::EMPTY() {
    return top == -1; // Проверяем, пуст ли стек
}

bool StackArray::FULL() {
    return top == MAX_SIZE - 1; // Проверяем, полон ли стек
}
