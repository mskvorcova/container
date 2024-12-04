#ifndef BUCKET_STORAGE_HPP
#define BUCKET_STORAGE_HPP
#include <cstddef>
#include "LinkedList.hpp"
#include "Block.hpp"
#include "Stack.hpp"

template<typename T>
class BucketStorage {
    using value_type = T;
    using size_type = size_t;

public:
    explicit BucketStorage() : capacity(64) {
        blocks = new LinkedList<Block<T>>[capacity];
    }

    explicit BucketStorage(size_type capacity) : capacity(capacity) {
        blocks = new LinkedList<Block<T>>[capacity];
    }

    ~BucketStorage() = default;

    void insert(T item) {
        if (free_blocks.empty()) {
            Block<value_type> block(capacity);
            block.add(item);
            blocks.append(block);
            if (blocks.getSize() > capacity) {
                free_blocks.push(block);
            }
        } else {
            Block<value_type> &free_block = free_blocks.peek();
            free_block.add(item);
            if (free_block.isFull()) {
                free_blocks.pop();
            }
        }
    }

private:
    LinkedList<Block<value_type> > blocks;
    LinkedList<value_type> elements;
    Stack<Block<value_type> &> free_blocks;
    size_type capacity;
    size_type current_size = 0;
};


#endif /* BUCKET_STORAGE_HPP */
