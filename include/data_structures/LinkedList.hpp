//
// Created by Reza on 7/04/2026.
//

#pragma once
#include "Node.hpp"
#include "../core/Debug.hpp"

template<typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    Node<T>* getHead() {
        return head;
    }

    const Node<T>* getHead() const {
        return head;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        int count = 0;
        Node<T>* current = head;

        while (current != nullptr) {
            count ++;
            current = current->next;
        }

        return count;
    }

    void clear() {
        Node<T>* current = head;

        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
    }

    template<typename Predicate>
    void removeIf(Predicate condition) {
        while (head != nullptr && condition(head->data)) {

            // Debug::log("Removing projectile from LinkedList");

            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        Node<T>* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (condition(current->next->data)) {

                // Debug::log("Removing projectile from LinkedList");
                
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            else {
                current = current->next;
            }
        }
    }
};