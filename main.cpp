/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 4: Registrar

main.cpp is the driver, handling file input and passing it to a registrar accordingly for data collection and analysis
*/

#include <iostream>
#include <fstream>
#include "Registrar.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Please pass filename as a command argument" << std::endl;
        exit(0);
    }
    std::string filename = argv[1];
    std::ifstream is(filename);
    if(is.fail()) {
        std::cerr << "Could not open '" << filename << "'.  Aborting." << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(is, line);
    int numWindows = stoi(line);
    Registrar r(numWindows);
    while(!is.eof()) {
        std::getline(is, line);
        int arrivalTick = stoi(line);
        if(is.eof()) {  //TODO: Refactor into method to check
            std::cerr << "Unexpected termination of file.  Exiting" << std::endl;
            exit(0);
        }
        std::getline(is, line);
        int numStudents = stoi(line);
        for(int i = 0; i < numStudents; ++i) {
            if(is.eof()) {  //TODO: Refactor into method to check
                std::cerr << "Unexpected termination of file.  Exiting" << std::endl;
                exit(0);
            }
            std::getline(is, line);
            int timeNeeded = stoi(line);
            Student* newStudent = new Student(arrivalTick, timeNeeded);
            r.addStudent(newStudent);
        }
    }

    while(!r.isOver()) {
        r.update();
    }
    r.prepareCalculations();
    std::cout << "Mean student wait time: " << r.calculateMeanStudentWaitTime() << std::endl;
    std::cout << "Median student wait time: " << r.calculateMedianStudentWaitTime() << std::endl;
    std::cout << "Longest student wait time: " << r.calculateLongestStudentWaitTime() << std::endl;
    std::cout << "Number of students waiting over 10 minutes: " << r.calculateNumStudentsWaitingOverTenMinutes() << std::endl;
    std::cout << "Mean window idle time: " << r.calculateMeanWindowIdleTime() << std::endl;
    std::cout << "Longest window idle time: " << r.calculateLongestWindowIdleTime() << std::endl;
    std::cout << "Number of windows idle over 5 minutes: " << r.calculateNumWindowsIdleOverFiveMinutes() << std::endl;
    return 0;
}