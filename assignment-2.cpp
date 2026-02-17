// assignment-2.cpp
// PHYS30762 Assignment 2 - Course Marks Data
// Roman le Bon - 11423027

// Include libraries needed for program to work

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>

std::ifstream course_marks{"course_marks.dat"}; // Open and attatch data from course_marks.dat to course_marks (read only)

// Create function to calculate mean
double mean(const std::vector<double>& mark, int record_count) { // Pass in the mark vector (& insures it uses the original and doesn't make a new copy) as a constant, so it cannot be altered

    double sum_xi{0};

    for (int index{0}; index < mark.size(); index++) { // Loops until all vector entries have been visited, increments index after each visit
        sum_xi += mark[index]; // Adds individual mark to rolling sum
    }

    double mu{sum_xi / record_count}; // Formula provided

    return mu;
  }

// Create function to calculate standard deviation 

double sd(const std::vector<double>& mark, int record_count, double mean) {

    double sxx{0};

    for (int index{0}; index < mark.size(); index++) {
        sxx += (mark[index] - mean) * (mark[index] - mean);
    }

    double sd{std::sqrt(sxx / (record_count - 1))}; // Formula provided

    return sd;
  }

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

    std::string line; // Declare string to hold a single line from the file 

    int record_count{0}; // Declare integer to count the number of records in the file

    // Read and store file data to the above defined vectors
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

            // Increment the count for the number of records by one
            record_count ++;

        }

        else {
            std::cerr << "Error: The data from the file could not be read." << std::endl; // Use error output to tell user the data can't be read
            return 1;
        }

    }

    std::cout << "Number of data entries (records): " << record_count << std::endl; // Output the number of records to the user 

    // Traverse and print all elements of the mark vector (by index)
    std::cout << "Full list of student marks:" << std::endl;

    for (int index{0}; index < mark.size(); index++) { // Loops until all vector entries have been visited, increments index after each visit
        std::cout << mark[index] << std::endl; // Outputs each mark entry to the user
    }

    return 0;
}
