#ifndef GENQUEUE_H
#define GENQUEUE_H
#include "DoublyLinkedList.cpp" //Including cpp for template

enum QueueException {
    QUEUE_EMPTY = 1
};

template<typename T>
class GenQueue {
    public:
        GenQueue(); //default constructor

        //core functions
        void insert(T d);
        T remove();
        void printList();

        //aux functions
        T peek();
        bool isEmpty();

        //vars
        int front; //aka head
        int rear; //aka tail
        int size;
        int numElements;
        int getSize();

        DoublyLinkedList<T> myQueue; //DoublyLinkedList
};
#endif