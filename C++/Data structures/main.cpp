#include <iostream>
#include "StackArray.h"
#include "QueueArray.h"
#include "MapLinkedList.h"

using namespace std;

int main() {
    // Тестирование стека на массиве
    StackArray stackArray;
    stackArray.PUSH('A');
    stackArray.PUSH('B');
    stackArray.PUSH('C');

    std::cout << "StackArray contents: ";
    while (!stackArray.EMPTY()) {
        std::cout << stackArray.POP() << " ";
    }
    std::cout << std::endl;

    // Тестирование очереди на массиве
    QueueArray queueArray;
    queueArray.ENQUEUE('X');
    queueArray.ENQUEUE('Y');
    queueArray.ENQUEUE('Z');

    std::cout << "QueueArray contents: ";
    while (!queueArray.EMPTY()) {
        std::cout << queueArray.DEQUEUE() << " ";
    }
    std::cout << std::endl;

    // Тестирование отображения на связном списке
    MapLinkedList mapLinkedList;
    mapLinkedList.ASSIGN(1, 10.5);
    mapLinkedList.ASSIGN(2, 20.3);
    mapLinkedList.ASSIGN(3, 30.7);

    std::cout << "MapLinkedList contents: ";
    for (int i = 1; i <= 3; ++i) {
        double value;
        if (mapLinkedList.COMPUTE(i, value)) {
            std::cout << value << " ";
        }
    }
    std::cout << std::endl;

    // Вывод адреса для существующего имени
    std::cout << "Address for existing name in MapLinkedList: " << &mapLinkedList << std::endl;

    // Вывод адреса для несуществующего имени
    MapLinkedList nonExistentMapLinkedList;
    std::cout << "Address for non-existing name in MapLinkedList: " << &nonExistentMapLinkedList << std::endl;

    return 0;
}
