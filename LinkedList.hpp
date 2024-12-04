#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template<typename T>
class LinkedList {
    using value_type = T;
    using size_type = size_t;
private:
    Node<T>* head;
    Node<T>* tail;
    size_type size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(const T& value) {
        auto* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void prepend(const T& value) {
        auto* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    void removeLast() {
        if (tail == nullptr) {
            std::cerr << "List is empty. Cannot remove last element." << std::endl;
            return;
        }

        Node<T>* temp = tail;
        if (tail->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
        --size;
    }

    void removeFirst() {
        if (head == nullptr) {
            std::cerr << "List is empty. Cannot remove first element." << std::endl;
            return;
        }

        Node<T>* temp = head;
        if (head->next != nullptr) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }

        delete temp;
        --size;
    }

    size_type getSize() const {
        return size;
    }

    void printList() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node<T>* find(const T& value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(Node<T>* node) {
        if (node == nullptr) {
            std::cerr << "Cannot remove a null node." << std::endl;
            return;
        }

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }

        delete node;
        --size;
    }
};

#endif //LINKEDLIST_HPP
