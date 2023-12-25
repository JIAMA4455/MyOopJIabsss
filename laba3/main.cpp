#include <iostream>
#include <string>
#include <algorithm> // Для std::swap

template<typename T>
class ScPtrArr {
public:
    explicit ScPtrArr(T* ptr = nullptr) : m_ptr(ptr) {}

    ~ScPtrArr() {
        delete[] m_ptr;
    }

    // Конструкторы копирования и оператор присваивания не должны быть доступны
    ScPtrArr(const ScPtrArr&) = delete;
    ScPtrArr& operator=(const ScPtrArr&) = delete;

    // Методы для работы с указателем
    void reset(T* ptr = nullptr) {
        delete[] m_ptr;
        m_ptr = ptr;
    }

    void swap(ScPtrArr& other) {
        std::swap(m_ptr, other.m_ptr);
    }

    T* get() const {
        return m_ptr;
    }

    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

    T& operator[](std::size_t index) {
        return m_ptr[index];
    }

    const T& operator[](std::size_t index) const {
        return m_ptr[index];
    }

    bool operator!() const {
        return m_ptr == nullptr;
    }

    explicit operator bool() const {
        return m_ptr != nullptr;
    }

private:
    T* m_ptr;
};

void demonstrateScPtrArr() {
    ScPtrArr<int> intArray(new int[10]);
    ScPtrArr<double> doubleArray(new double[5]);
    ScPtrArr<std::string> stringArray(new std::string[3]);

    // Пример использования
    for (int i = 0; i < 10; i++) {
        intArray[i] = i;
    }
    for (int i = 0; i < 5; i++) {
        doubleArray[i] = i * 2.5;
    }
    stringArray[0] = "Hello";
    stringArray[1] = "World";
    stringArray[2] = "!";

    // Вывод результатов
    for (int i = 0; i < 10; i++) {
        std::cout << intArray[i] << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << doubleArray[i] << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << stringArray[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    demonstrateScPtrArr();
    return 0;
}
