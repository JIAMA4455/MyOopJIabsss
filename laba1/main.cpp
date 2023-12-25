#include <iostream>
#include <initializer_list>
#include <string>

namespace containers {

    template<typename T>
    class NameClass {
    public:
        struct Node {
        public:
            T value;

        private:
            Node* next;
            Node* prev;

            Node(T val) : value(val), next(this), prev(this) {}

            friend class NameClass;

        };

        NameClass() : head(nullptr), size(0) {}

        NameClass(std::initializer_list<T> list) : NameClass() {
            for (auto& item : list) {
                add(item);
            }
        }

        NameClass(const NameClass& other) : NameClass() {
            Node* current = other.head;
            if (current) {
                do {
                    add(current->value);
                    current = current->next;
                } while (current != other.head);
            }
        }

        NameClass& operator=(const NameClass& other) {
            if (this != &other) {
                clear();
                Node* current = other.head;
                if (current) {
                    do {
                        add(current->value);
                        current = current->next;
                    } while (current != other.head);
                }
            }
            return *this;
        }

        NameClass(NameClass&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        NameClass& operator=(NameClass&& other) noexcept {
            if (this != &other) {
                clear();
                head = other.head;
                size = other.size;
                other.head = nullptr;
                other.size = 0;
            }
            return *this;
        }

        ~NameClass() {
            clear();
        }

        void add(const T& value) {
            Node* newNode = new Node(value);
            if (!head) {
                head = newNode;
            } else {
                newNode->prev = head->prev;
                newNode->next = head;
                head->prev->next = newNode;
                head->prev = newNode;
            }
            size++;
        }

        void remove() {
            if (!head) return;
            if (size == 1) {
                delete head;
                head = nullptr;
            } else {
                Node* toDelete = head->prev;
                toDelete->prev->next = head;
                head->prev = toDelete->prev;
                delete toDelete;
            }
            size--;
        }

        T& operator[](int index) {
            Node* current = head;
            for (int i = 0; i < index % size; i++) {
                current = current->next;
            }
            return current->value;
        }

        int getSize() const {
            return size;
        }

    private:
        Node* head;
        int size;

        void clear() {
            while (size > 0) {
                remove();
            }
        }
    };
}

int main() {
    containers::NameClass<int> intList {1, 2, 3};
    containers::NameClass<double> doubleList {1.1, 2.2, 3.3};
    containers::NameClass<std::string> stringList {"one", "two", "three"};

    // Демонстрация работы с классом
    std::cout << "Int List: ";
    for (int i = 0; i < intList.getSize(); ++i) {
        std::cout << intList[i] << " ";
    }
    std::cout << std::endl;

    // Подобное можно продемонстрировать для doubleList и stringList

    return 0;
}
