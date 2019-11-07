#ifndef REGISTRAR_H
#define REGISTRAR_H
#include "Window.h" //Includes Student.h in Window.h
#include "GenQueue.cpp" //Including cpp because template
class Registrar {
    public:
        Registrar();
        Registrar(int numWindows);
        ~Registrar();
        void update();
        void addStudent(Student* someStudent);
        void prepareCalculations();
        double calculateMeanStudentWaitTime();
        float calculateMedianStudentWaitTime();
        int calculateLongestStudentWaitTime();
        int calculateNumStudentsWaitingOverTenMinutes();
        double calculateMeanWindowIdleTime();
        int calculateLongestWindowIdleTime();
        int calculateNumWindowsIdleOverFiveMinutes();
        bool isOver();
    private:
        Window* windows;
        int numWindows;
        int numStudents;
        GenQueue<Student*> line;
        GenQueue<Student*> preline; //NOTE: May need to make it a double ended linked list instead if students are given out of order
        GenQueue<Student*> postline;
        int currentTick;
        int* waitTimes;
        int* idleTimes;
};
#endif