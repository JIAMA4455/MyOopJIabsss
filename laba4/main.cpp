#include <iostream>
#include <initializer_list>
#include <vector>

template<typename T>
class Queue {
public:
    Queue() {}

    Queue(std::initializer_list<T> init) : data(init) {}

    Queue(const Queue& other) : data(other.data) {}

    Queue(Queue&& other) noexcept : data(std::move(other.data)) {}

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    void enqueue(const T& value) {
        data.push_back(value);
    }

    void dequeue() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }

    T& front() {
        if (!data.empty()) {
            return data.front();
        }
        throw std::out_of_range("Queue is empty");
    }

    const T& front() const {
        if (!data.empty()) {
            return data.front();
        }
        throw std::out_of_range("Queue is empty");
    }

    bool isEmpty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

private:
    std::vector<T> data;
};

int main() {
    Queue<int> intQueue;
    intQueue.enqueue(1);
    intQueue.enqueue(2);
    intQueue.enqueue(3);

    Queue<double> doubleQueue({1.1, 2.2, 3.3});

    Queue<std::string> stringQueue;
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");

    // Демонстрация работы с очередью
    while (!intQueue.isEmpty()) {
        std::cout << "Int Queue Front: " << intQueue.front() << std::endl;
        intQueue.dequeue();
    }

    while (!doubleQueue.isEmpty()) {
        std::cout << "Double Queue Front: " << doubleQueue.front() << std::endl;
        doubleQueue.dequeue();
    }

    while (!stringQueue.isEmpty()) {
        std::cout << "String Queue Front: " << stringQueue.front() << std::endl;
        stringQueue.dequeue();
    }

    return 0;
}
