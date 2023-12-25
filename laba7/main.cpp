#include <iostream>
#include <initializer_list>
#include <vector>
#include <stdexcept>

class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception occurred";
    }
};

template<typename T>
class Queue {
public:
    Queue() {}

    Queue(std::initializer_list<T> init) : data_(init) {}

    Queue(const Queue& other) : data_(other.data_) {}

    Queue(Queue&& other) noexcept : data_(std::move(other.data_)) {}

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    void enqueue(const T& value) {
        data_.push_back(value);
    }

    void dequeue() {
        if (!data_.empty()) {
            data_.erase(data_.begin());
        }
    }

    T& front() {
        if (!data_.empty()) {
            return data_.front();
        }
        throw std::out_of_range("Queue is empty");
    }

    const T& front() const {
        if (!data_.empty()) {
            return data_.front();
        }
        throw std::out_of_range("Queue is empty");
    }

    class PositiveIterator {
    public:
        PositiveIterator(std::vector<T>& data, size_t index = 0) : data_(data), index_(index) {
            moveToNextPositive();
        }

        T& operator*() {
            if (index_ >= data_.size()) {
                throw CustomException();
            }
            return data_[index_];
        }

        PositiveIterator& operator++() {
            index_++;
            moveToNextPositive();
            return *this;
        }

        bool operator!=(const PositiveIterator& other) const {
            return index_ != other.index_;
        }

    private:
        std::vector<T>& data_;
        size_t index_;

        void moveToNextPositive() {
            while (index_ < data_.size() && data_[index_] <= 0) {
                index_++;
            }
        }
    };

    class NegativeIterator {
    public:
        NegativeIterator(std::vector<T>& data, size_t index = 0) : data_(data), index_(index) {
            moveToNextNegative();
        }

        T& operator*() {
            if (index_ >= data_.size()) {
                throw CustomException();
            }
            return data_[index_];
        }

        NegativeIterator& operator++() {
            index_++;
            moveToNextNegative();
            return *this;
        }

        bool operator!=(const NegativeIterator& other) const {
            return index_ != other.index_;
        }

    private:
        std::vector<T>& data_;
        size_t index_;

        void moveToNextNegative() {
            while (index_ < data_.size() && data_[index_] >= 0) {
                index_++;
            }
        }
    };

    PositiveIterator beginPositive() {
        return PositiveIterator(data_);
    }

    PositiveIterator endPositive() {
        return PositiveIterator(data_, data_.size());
    }

    NegativeIterator beginNegative() {
        return NegativeIterator(data_);
    }

    NegativeIterator endNegative() {
        return NegativeIterator(data_, data_.size());
    }

private:
    std::vector<T> data_;
};

int main() {
    Queue<int> queue = {1, -2, 3, -4, 5};
    for (auto it = queue.beginPositive(); it != queue.endPositive(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (auto it = queue.beginNegative(); it != queue.endNegative(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
