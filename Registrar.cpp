/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 4: Registrar

Registrar.cpp is the core implementation of a registrar, handling update logic and storing students and windows as needed.
*/

#include "Registrar.h"
#include <algorithm> //For std::sort

/*
    Default Constructor: dynamically allocates memory and initializes variables as needed
*/
Registrar::Registrar() {
    windows = new Window[3];
    this->numWindows = 3;
    currentTick = 1;
}

/*
    Overloaded Constructor: dynamically allocates memory and initializes variables as needed
    numWindows: number of windows desired in the simulation
*/
Registrar::Registrar(int numWindows) {
    windows = new Window[numWindows];
    this->numWindows = numWindows;
    currentTick = 1;
}

/*
    Destructor: cleans up memory as needed
*/
Registrar::~Registrar() {
    delete windows;
}

/*
    Adds a student to the simulation by adding them to the preline
*/
void Registrar::addStudent(Student* someStudent) {
    preline.insert(someStudent);
}

/*
    Contains the update logic for each clock tick
*/
void Registrar::update() {
    //NOTE: Assumes students were given in order, but uses <= to prevent infinite looping if students aren't
    while(!preline.isEmpty() && preline.peek()->getArrivalTick() <= currentTick) { //If a student entered the line this tick, then add them to the line
        line.insert(preline.remove());
    }

    for(int i = 0; i < numWindows; ++i) {
        if(windows[i].getCurrentStudent() != nullptr) {     //Decrement timeNeeded for every student at a window
            windows[i].getCurrentStudent()->setTimeNeeded((windows[i].getCurrentStudent()->getTimeNeeded()) - 1); //TODO: Fix up this line
            if(windows[i].getCurrentStudent()->getTimeNeeded() == 0) {    //For every window, if the student at the window has timeNeeded of 0, remove them
                postline.insert(windows[i].getCurrentStudent());
                windows[i].setCurrentStudent(nullptr);
            }
        }
    }

    while(!line.isEmpty()) {
        //Take student from line and put at an empty window.  If no empty windows break
        bool windowOpen = false;
        for(int i = 0; i < numWindows; ++i) {
            if(windows[i].getCurrentStudent() == nullptr) {
                windowOpen = true;
                windows[i].setCurrentStudent(line.remove());
                break;
            }
        }
        if(!windowOpen) {
            break;
        }
    }

    //Increment window idle time if simulation has not ended
    if(!isOver()) {
        for(int i = 0; i < numWindows; ++i) {
            if(windows[i].getCurrentStudent() == nullptr) {
                windows[i].setIdleTime(windows[i].getIdleTime() + 1);
            }
        }
    }
    //Increment wait time
    ListNode<Student*>* curr = line.myQueue.front;
    while(curr != nullptr) {
        curr->data->setWaitTime(curr->data->getWaitTime() + 1);
        curr = curr->next;
    }
    ++currentTick;
}

/*
    Checks whether or not the simulation has completed
    Returns true if the simulation has completed, false otherwise
*/
bool Registrar::isOver() {
    bool windowsEmpty = true;
    for(int i = 0; i < numWindows; ++i) {   //Check if windows are empty
        if(windows[i].getCurrentStudent() != nullptr) {
            windowsEmpty = false;
            break;
        }
    }
    return preline.isEmpty() && line.isEmpty() && windowsEmpty;
}

/*
    Prepares calculations by initializing waitTimes and idleTimes as arrays to simplify calculations
*/
void Registrar::prepareCalculations() {
    waitTimes = new int[postline.numElements];
    idleTimes = new int[numWindows];
    numStudents = postline.numElements; //Can't use postline.numElements because we're modifying that by removing students
    for(int i = 0; i < numStudents; ++i) {  //Initialize waitTimes
        Student* temp = postline.remove();
        waitTimes[i] = temp->getWaitTime();
        delete(temp);   //Memory cleanup
    }
    std::sort(waitTimes, waitTimes + numStudents);
    for(int i = 0; i < numWindows; ++i) {   //Initialize idleTimes
        idleTimes[i] = windows[i].getIdleTime();
    }
}

/*
    Calculates the mean student wait time based on the waitTimes array initialized in prepareCalculations()
    Returns the mean student wait time
*/
double Registrar::calculateMeanStudentWaitTime() {
    double totalStudentWaitTime = 0;
    for(int i = 0; i < numStudents; ++i)  {
        totalStudentWaitTime += waitTimes[i];
    }
    return totalStudentWaitTime/numStudents;
}

/*
    Calculates the median student wait time based on the waitTimes array initialized in prepareCalculations()
    Returns the median student wait time
*/
float Registrar::calculateMedianStudentWaitTime() {
    int tempNumStudents = numStudents; //Making copy of numStudents so we can modify it without affecting the value itself.
    int i = 0; //Initializing i locally outside of the loop so we can compare it to tempNumStudents after the loop's execution.
    for(i = 0; i < tempNumStudents - 1; ++i) {
        ++i;
        --tempNumStudents;
    }
    if(i == tempNumStudents) {
        return waitTimes[i];
    } else { //i = tempNumStudents - 1
        return float(waitTimes[i] + waitTimes[i + 1])/2;
    }
}

/*
    Calculates the longest student wait time based on the waitTimes array initialized in prepareCalculations()
    Returns the longest student wait time
*/
int Registrar::calculateLongestStudentWaitTime() {
    int longestWaitTime = 0;
    for(int i = 0; i < numStudents; ++i) {
        if(waitTimes[i] > longestWaitTime) {
            longestWaitTime = waitTimes[i];
        }
    }
    return longestWaitTime;
}

/*
    Calculates the amount of students waiting over 10 minutes using the waitTimes array initialized in prepareCalculations()
    Returns the number of students who have waited over 10 minutes
*/
int Registrar::calculateNumStudentsWaitingOverTenMinutes() {
    int numStudentsWaitingOverTenMinutes = 0;
    for(int i = 0; i < numStudents; ++i) {
        if(waitTimes[i] > 10) {
            ++numStudentsWaitingOverTenMinutes;
        }
    }
    return numStudentsWaitingOverTenMinutes;
}

/*
    Calculates the mean window idle time based on the idleTimes array initialized in prepareCalculations()
    Returns the mean window idle time
*/
double Registrar::calculateMeanWindowIdleTime() {
    double totalIdleTime = 0;
    for(int i = 0; i < numWindows; ++i) {
        totalIdleTime += idleTimes[i];
    }
    return totalIdleTime/numWindows;
}

/*
    Calculates the longest window idle time based on the idleTimes array initialized in prepareCalculations()
    Returns the longest window idle time
*/
int Registrar::calculateLongestWindowIdleTime() {
    int longestIdleTime = 0;
    for(int i = 0; i < numWindows; ++i) {
        if(idleTimes[i] > longestIdleTime) {
            longestIdleTime = idleTimes[i];
        }
    }
    return longestIdleTime;
}

/*
    Calculates the number of windows idle for over five minutes using the idleTimes array initialized in prepareCalculations()
    Returns the number of windows idle for over five minutes
*/
int Registrar::calculateNumWindowsIdleOverFiveMinutes() {
    int numWindowsIdleOverFiveMinutes = 0;
    for(int i = 0; i < numWindows; ++i) {
        if(idleTimes[i] > 5) {
            ++numWindowsIdleOverFiveMinutes;
        }
    }
    return numWindowsIdleOverFiveMinutes;
}
