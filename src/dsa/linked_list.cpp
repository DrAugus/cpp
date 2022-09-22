//
// linked_list.cpp
// Created by AUGUS on 2022/7/5.
//

#include <iostream>
#include <random>

struct LinkedListNode {
    int key;
    int value;
    LinkedListNode *next;
};

// TODO
// Singly linked list

//Insertion − Adds an element at the beginning of the list.
//Deletion − Deletes an element at the beginning of the list.
//Insert Last − Adds an element at the end of the list.
//Delete Last − Deletes an element from the end of the list.
//Insert After − Adds an element after an item of the list.
//Delete − Deletes an element from the list using the key.
//Display forward − Displays the complete list in a forward manner.
//Display backward − Displays the complete list in a backward manner.
struct DoublyLinkedListNode : LinkedListNode {
    int key;
    int value;
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
};

struct DoublyLinkedListNode *head = nullptr;
struct DoublyLinkedListNode *tail = nullptr;

bool isEmpty() {
    return head == nullptr;
}

int length() {
    int length = 0;
    while (head->next) {
        ++length;
    }
    return length;
}

void displayForward() {
    auto *p = head;
    std::cout << "[";
    while (p) {
        std::cout << "(" << p->key << "," << p->value << ")";
        p = p->next;
    }
    std::cout << "]\n";
}

void displayBackward() {
    auto *p = tail;
    std::cout << "[";
    while (p) {
        std::cout << "(" << p->key << "," << p->value << ")";
        p = p->prev;
    }
    std::cout << "]\n";
}

DoublyLinkedListNode *create(int len) {
    if (len <= 0) {
        std::cerr << "wrong length" << std::endl;
    }
    std::random_device rd;
    head = nullptr;
    tail = nullptr;

    int key = 0;
    while (--len) {
        auto *link = new DoublyLinkedListNode;
        link->key = ++key;
        link->value = (int) rd();

        if (key == 1) {
            tail = link;
            link->next = head;
            head = link;
            continue;
        }

        auto *current = head;
        if (current == tail) {
            link->next = nullptr;
            tail = link;
        } else {
            link->next = current->next;
            current->next->prev = link;
        }
        link->prev = current;
        current->next = link;

    }
    return head;
}

bool insert(int insertPos, int key, int value) {
    auto *link = new DoublyLinkedListNode;
    link->key = key;
    link->value = value;

    if (insertPos == 0) {
        // insert head
        if (isEmpty()) {
            tail = link;
        } else {
            head->prev = link;
        }
        link->next = head;
        head = link;
    } else if (insertPos == length()) {
        // insert tail
        if (isEmpty()) {
            tail = link;
        } else {
            tail->next = link;
            link->prev = tail;
        }
        tail = link;
    } else {
        if (isEmpty()) return false;
        auto *current = head;
        while (current->key != key) {
            if (current->next) {
                current = current->next;
                continue;
            }
            return false;
        }
        if (current == tail) {
            link->next = nullptr;
            tail = link;
        } else {
            link->next = current->next;
            current->next->prev = link;
        }
        link->prev = current;
        current->next = link;
    }
    return true;
}


int main() {
//    displayForward();
    return 0;
}