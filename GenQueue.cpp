/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 4: Registrar

GenQueue.cpp is the template implementation of a Queue using a doubly linked list
*/

#include "GenQueue.h"
using namespace std;

/*
    Default constructor: initializes values as needed
*/
template <typename T>
GenQueue<T>::GenQueue() {
    size = 0;
    front = 0;
    rear = -1;
    numElements = 0;
}

//core functions
/*
    Inserts an item into the Queue
    d: data to be inserted into the queue
*/
template <typename T>
void GenQueue<T>::insert(T d) {
    if(rear == size-1) {
        rear = -1;
    }
    myQueue.insertBack(d);
    ++rear;
    ++numElements;
}

/*
    Removes an item from the queue
    Returns data removed from the queue
*/
template <typename T>
T GenQueue<T>::remove() {
    if(isEmpty()) {
        //TODO: throw QueueEmptyException
        throw QueueException::QUEUE_EMPTY;
    }
    --numElements;
    return myQueue.removeFront();
}

//aux functions
/*
    Peeks at the first item in the queue
    Returns the first item in the queue without removing it
*/
template <typename T>
T GenQueue<T>::peek() {
    return (myQueue.front)->data;
}

/*
    Checks if the queue is empty
    Returns true if the queue is empty, false otherwise
*/
template <typename T>
bool GenQueue<T>::isEmpty() {
    return (numElements == 0);
}

/*
    Accessor for numElements
    Returns the number of elements in the Queue
*/
template <typename T>
int GenQueue<T>::getSize() {
    return numElements;
}

/*
    Prints a list of the items in the queue
*/
template <typename T>
void GenQueue<T>::printList() {
    myQueue.printList();
}
