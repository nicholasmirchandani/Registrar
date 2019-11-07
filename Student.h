#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student {
    public:
        Student();
        Student(int arrivalTick, int timeNeeded);
        int getArrivalTick();
        void setArrivalTick(int arrivalTick);
        int getTimeNeeded();
        void setTimeNeeded(int timeNeeded);
        int getWaitTime();
        void setWaitTime(int waitTime);
        friend std::ostream& operator<< (std::ostream& os, const Student& student);
    private:
        int arrivalTick;
        int timeNeeded;
        int waitTime;
};
#endif