// Package: QueueArray
#include <iostream>

// Замените ElementType на фактический тип вашего элемента
using ElementType = int;

class QueueArray {
public:
    QueueArray(); // Конструктор
    void MAKENULL(); // Очищает очередь, делая ее пустой.
    ElementType FRONT(); // Возвращает первый элемент очереди.
    ElementType DEQUEUE(); // Удаляет первый элемент очереди и возвращает его.
    void ENQUEUE(ElementType x); // Вставляет элемент x в конец очереди.
    bool EMPTY(); // Возвращает true, если очередь пуста, и false в противном случае.
    bool FULL(); // Возвращает true, если очередь полна, и false в противном случае.

private:
    static const int MAX_SIZE = 100; // Задайте максимальный размер очереди
    ElementType queue[MAX_SIZE]; // Массив для хранения элементов очереди
    int front; // Индекс начала очереди
    int rear; // Индекс конца очереди

};

// Определение методов класса QueueArray
QueueArray::QueueArray() {
    MAKENULL();
}

void QueueArray::MAKENULL() {
    front = rear = -1; // Устанавливаем начало и конец очереди в -1, делая ее пустой
}

ElementType QueueArray::FRONT() {
    if (!EMPTY()) {
        return queue[front]; // Возвращаем элемент из начала очереди
    } else {
        std::cerr << "Error: Queue is empty." << std::endl;
        return 0;
    }
}

ElementType QueueArray::DEQUEUE() {
    if (!EMPTY()) {
        ElementType dequeuedItem = queue[front];
        if (front == rear) {
            MAKENULL(); // Если удаляем последний элемент, делаем очередь пустой
        } else {
            front = (front + 1) % MAX_SIZE; // Увеличиваем индекс начала, учитывая кольцевую структуру
        }
        return dequeuedItem;
    } else {
        std::cerr << "Error: Queue is empty." << std::endl;
        return 0;
    }
}

void QueueArray::ENQUEUE(ElementType x) {
    if (!FULL()) {
        if (EMPTY()) {
            front = rear = 0; // Если очередь была пустой, устанавливаем начало и конец на 0
        } else {
            rear = (rear + 1) % MAX_SIZE; // Увеличиваем индекс конца, учитывая кольцевую структуру
        }
        queue[rear] = x; // Добавляем элемент в конец очереди
    } else {
        std::cerr << "Error: Queue is full." << std::endl;
        return;
    }
}

bool QueueArray::EMPTY() {
    return front == -1 && rear == -1; // Проверяем, пуста ли очередь
}

bool QueueArray::FULL() {
    return (rear + 1) % MAX_SIZE == front; // Проверяем, полна ли очередь
}
