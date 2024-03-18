#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

template <typename T>
class HashTable {
private:
    int n;  // Размер таблицы
    int a;  // Параметр хэш-функции
    int b;  // Параметр хэш-функции
    std::vector<std::vector<T>> table;  // Хранилище данных
    
    // Хэш-функция для строк
    int hashFunction(const std::string& key) const {
        int sum = 0;
        for (char ch : key) {
            sum += static_cast<int>(ch);
        }
        return (a * sum + b) % n;
    }
    
public:
    // Конструктор с параметрами
    HashTable(int size, int paramA, int paramB) : n(size), a(paramA), b(paramB), table(size) {}
    
    // Добавление элемента в таблицу
    void operator+(const T& element) {
        int index = hashFunction(element);
        table[index].push_back(element);
    }
    
    // Получение размера таблицы
    int GetSize() const {
        return n;
    }
    
    // Возвращение i-того ведра таблицы
    const std::vector<T>& GetBucket(int i) const {
        return table[i];
    }
    
    // Вывод таблицы
    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
        for (const auto& bucket : hashTable.table) {
            for (const auto& element : bucket) {
                os << element << " ";
            }
        }
        return os;
    }
    
    // Реализация оператора ==
    bool operator==(const HashTable& other) const {
        return table == other.table;
    }
    
    // Реализация оператора +
    HashTable operator+(const HashTable& other) const {
        HashTable result(n, a, b);
        
        for (int i = 0; i < n; ++i) {
            result.table[i].insert(result.table[i].end(), other.table[i].begin(), other.table[i].end());
            result.table[i].insert(result.table[i].end(), table[i].begin(), table[i].end());
        }
        
        return result;
    }
    
    // Реализация оператора -
    void operator-(const T& element) {
        for (auto& bucket : table) {
            auto it = std::remove(bucket.begin(), bucket.end(), element);
            bucket.erase(it, bucket.end());
        }
    }
    
    bool search(const T& element) const {
        for (const auto& bucket : table) {
            if (std::find(bucket.begin(), bucket.end(), element) != bucket.end()) {
                return true;
            }
        }
        return false;
    }
};



int main() {
    // Параметры создания таблицы Т1
    int sizeT1, paramAT1, paramBT1;
    std::cout << "Enter size, parameter A, and parameter B for table T1: ";
    std::cin >> sizeT1 >> paramAT1 >> paramBT1;
    HashTable<std::string> T1(sizeT1, paramAT1, paramBT1);
    
    // Загрузка ключевых слов в T1 из файла "in1.txt"
    std::ifstream inFile1("in1.txt");
    if (inFile1.is_open()) {
        std::string word;
        while (inFile1 >> word) {
            T1 + word;
        }
        inFile1.close();
        std::cout << "Table T1:\n" << T1 << "\n\n";
    } else {
        std::cerr << "Error: Unable to open file 'in1.txt'\n";
        return 1;
    }
    
    // Загрузка текста из файла "in2.txt"
    std::ifstream inFile2("in2.txt");
    if (inFile2.is_open()) {
        std::cout << "Words in 'in2.txt' that match with keys in T1:\n";
        std::string word;
        while (inFile2 >> word) {
            if (T1.search(word)) {
                std::cout << word << " ";
            }
        }
        std::cout << "\n\n";
        inFile2.close();
    } else {
        std::cerr << "Error: Unable to open file 'in2.txt'\n";
        return 1;
    }
    
    // Создание таблиц T2 и T3
    int sizeT2, paramAT2, paramBT2, sizeT3, paramAT3, paramBT3;
    std::cout << "Enter size, parameter A, and parameter B for table T2: ";
    std::cin >> sizeT2 >> paramAT2 >> paramBT2;
    HashTable<std::string> T2(sizeT2, paramAT2, paramBT2);
    
    std::cout << "Enter size, parameter A, and parameter B for table T3: ";
    std::cin >> sizeT3 >> paramAT3 >> paramBT3;
    HashTable<std::string> T3(sizeT3, paramAT3, paramBT3);
    
    // Загрузка данных в T2 и T3 из файлов "in3.txt" и "in4.txt"
    std::ifstream inFile3("in3.txt");
    if (inFile3.is_open()) {
        std::string word;
        while (inFile3 >> word) {
            T2 + word;
        }
        inFile3.close();
        std::cout << "Table T2:\n" << T2 << "\n\n";
    } else {
        std::cerr << "Error: Unable to open file 'in3.txt'\n";
        return 1;
    }
    
    std::ifstream inFile4("in4.txt");
    if (inFile4.is_open()) {
        std::string word;
        while (inFile4 >> word) {
            T3 + word;
        }
        inFile4.close();
        std::cout << "Table T3:\n" << T3 << "\n\n";
    } else {
        std::cerr << "Error: Unable to open file 'in4.txt'\n";
        return 1;
    }
    
    // Проверка совпадения таблиц T1 и T2
    if (T1 == T2) {
        std::cout << "Tables T1 and T2 are equal.\n\n";
    } else {
        // Объединение таблиц T1 и T2 в T4
        HashTable<std::string> T4 = T1 + T2;
        std::cout << "Table T4 (union of T1 and T2):\n" << T4 << "\n\n";
        
        // Проверка совпадения таблиц T3 и T4
        if (T3 == T4) {
            std::cout << "Tables T3 and T4 are equal.\n\n";
        } else {
            // Удаление из T3 элементов, которые есть в T4
            for (const auto& bucket : T4.GetBucket(0)) {
                T3 - bucket;
            }
            std::cout << "Table T3 after removing elements present in T4:\n" << T3 << "\n\n";
        }
    }
    
    return 0;
}



