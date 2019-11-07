/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 4: Registrar

Student.cpp is the implementation of a student, storing data as needed
*/


#include "Student.h"

/*
    Default Constructor: is empty but exists because good practice
*/
Student::Student() {
    //Empty Default Constructor
}

/*
    Overloaded constructor: creates a student with the desired data values
    arrivalTick: tick the student will arrive in the simulation
    timeNeeded: amount of time the student needs at a window
*/
Student::Student(int arrivalTick, int timeNeeded) {
    this->arrivalTick = arrivalTick;
    this->timeNeeded = timeNeeded;
}

/*
    Operator overload of << specifically with ostreams to allow Stuents to be easily written to anything.
    os: output stream writing to
    s: student being written
    Returns initial output stream after performing operations to allow for recursive calling and chaining together of <<'s
*/
std::ostream& operator<<(std::ostream& os, const Student& s) { //Operator Overload
    os << "{ Arrival Tick: " << s.arrivalTick << " Time Needed: " << s.timeNeeded <<  " Wait Time: " << s.waitTime << " }";
    return os;
}

/*
    Accessor for arrivalTick
    Returns the tick the student will arrive
*/
int Student::getArrivalTick() {
    return arrivalTick;
}

/*
    Accessor for timeNeeded
    Returns the time a student needs at a window
*/
int Student::getTimeNeeded() {
    return timeNeeded;
}

/*
    Mutator for time needed
    timeNeeded: time student needs at a window
*/
void Student::setTimeNeeded(int timeNeeded) {
    this->timeNeeded = timeNeeded;
}

/*
    Accessor for wait time
    Returns time waited in line
*/
int Student::getWaitTime() {
    return waitTime;
}

/*
    Mutator for wait time
    waitTime: time student has waited in line
*/
void Student::setWaitTime(int waitTime) {
    this->waitTime = waitTime;
}