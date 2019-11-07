#ifndef WINDOW_H
#define WINDOW_H
#include "Student.h"
class Window {
    public:
        Window();
        bool isOpen();
        Student* getCurrentStudent();
        void setCurrentStudent(Student* currentStudent);
        int getIdleTime();
        void setIdleTime(int idleTime);
    private:
        int idleTime;
        Student* currentStudent;
};
#endif