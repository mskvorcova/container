#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>

template <typename T>
struct StackNode {
    using value_type = T;
    value_type data;
    StackNode* next;

    explicit StackNode(value_type value) : data(value), next(nullptr) {}
};

template <typename T>
class Stack {
    using value_type = T;
    using size_type = size_t;
private:
    StackNode<value_type>* top;
    size_type size;
    public:
    Stack() : top(nullptr), size(0) {}
    ~Stack() {while (size != 0) pop();}
    void push(value_type value) {
        StackNode<value_type>* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
        size++;
    }
    void pop() {
        if (top == nullptr) {
            throw std::out_of_range("Stack is empty");
        } else {
            StackNode<value_type>* temp = top;
            top = top->next;
            size--;
            delete temp;
        }
    }

    value_type peek() {
        if (top == nullptr) {
            return -1;
        } else {
            return top->data;
        }
    }

    bool empty() {
        return size == 0;
    }

};
#endif //STACK_HPP
