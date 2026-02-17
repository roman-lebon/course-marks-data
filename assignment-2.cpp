// assignment-2.cpp
// PHYS30762 Assignment 2 - Course Marks Data
// Roman le Bon - 11423027

// Include libraries needed for program to work

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

std::ifstream course_marks{"course_marks.dat"}; // Open and attatch data from course_marks.dat to course_marks (read only)

int main() {

    // Check that the file is successfully opened 
    if (!course_marks.is_open()) {
        std::cerr << "Error: The file could not be opened." << std::endl; // Use error output to tell user the file can't be opened
        return 1;
    }

    // Declare vectors to store the data read from the file 
    std::vector<double> mark; // Integer (decimal) vector for the student's mark
    std::vector<std::string> code; // String vector for the course code 
    std::vector<std::string> name; // String vector for the course name

    // Read the data from the file

    std::string line; // Declare string to hold a single line from the file 
    
    while (std::getline(course_marks, line)) {

        std::stringstream ss(line); // Create a stream from the line so we can extract and seperate the different data

        // Use temporary variables to store data from the single line
        double line_mark;
        std::string line_code;
        std::string line_name; 

        // Extract the data if formatted correctly 

        if (ss >> line_mark >> line_code) { 

            // If mark and course code is successfully extracted we must handle the extraction of the course name differently 
            // Extracting normally would only retrieve the first word of the course name
            std::getline(ss, line_name); // Extracts the rest of the string stream (including spaces)

            // If there is a valid name, containing an intial whitespace, we remove erase the first character (the space)
            if (!line_name.empty() && line_name[0] == ' ') {
                line_name.erase(0,1);
            }

            // Store extracted values to relevant vectors
            mark.push_back(line_mark);
            code.push_back(line_code);
            name.push_back(line_name); 

        }

        else {
            std::cerr << "Error: The data from the file could not be read." << std::endl; // Use error output to tell user the data can't be read
            return 1;
        }

    }

    return 0;
}
