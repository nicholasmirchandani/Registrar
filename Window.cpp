/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 4: Registrar

Window.cpp is the implementation of a window, storing data as needed
*/


#include "Window.h"

/*
    Default constructor: Initializes variables as needed
*/
Window::Window() {
    idleTime = 0;
    currentStudent = nullptr;
}

/*
    Accessor for currentStudent
    returns pointer to the student currently at the window
*/
Student* Window::getCurrentStudent() {
    return currentStudent;
}

void Window::setCurrentStudent(Student* currentStudent) {
    this->currentStudent = currentStudent;
}

int Window::getIdleTime() {
    return idleTime;
}

void Window::setIdleTime(int idleTime) {
    this->idleTime = idleTime;
}