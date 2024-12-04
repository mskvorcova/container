#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "Stack.hpp"
template <typename T>
class Block {
    using value_type = T;
    using size_type = size_t;
private:
    value_type* elements;
    Stack<value_type> freeIndices;
    size_type usedCount;
    const size_type block_capacity;
public:
    explicit Block(size_type capacity = 64) : block_capacity(capacity), usedCount(0) {
        freeIndices = new Stack<value_type>(block_capacity);
        elements = new T[block_capacity];
        for (size_type i = 0; i < block_capacity; ++i) {
            freeIndices.push(i);
        }
    }
    ~Block() {
        delete[] elements;
    }
    size_type add(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Block is full. Cannot add new element.");
        }

        std::size_t index = freeIndices.pop();
        elements[index] = value;
        ++usedCount;
        return index;
    }
    void remove(size_type index) {
        if (index >= block_capacity || isEmpty()) {
            throw std::out_of_range("Invalid index or block is empty.");
        }
        elements[index].~T();
        freeIndices.push(index);
        --usedCount;
    }

    [[nodiscard]] bool isEmpty() const {
        return usedCount == 0;
    }
    [[nodiscard]] bool isFull() const {
        return usedCount == block_capacity;
    }
    T& get(size_type index) {
        if (index >= block_capacity) {
            throw std::out_of_range("Invalid index.");
        }
        return elements[index];
    }
};
#endif //BLOCK_HPP
