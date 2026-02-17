// assignment-2.cpp
// PHYS30762 Assignment 2 - Course Marks Data
// Roman le Bon - 11423027

// Include libraries needed for program to work

#include<iostream>
#include<fstream>

std::ifstream course_marks{"course_marks.dat"}; // Open and attatch data from course_marks.dat to course_marks (read only)

int main() {

    // Check that the file is successfully opened 
    if (!course_marks.good()) {
        std::cerr << "Error: The file could not be opened." << std::endl; // Use error output to tell user the file can't be opened
        return(1);
    }

    return(0);
}
