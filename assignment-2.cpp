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

// Create function to calculate standard error
double se(double sd, int record_count) {

    double se{sd/(std::sqrt(record_count))}; // Formula provided

    return se;
  }

int main() {

    // Check that the file is successfully opened 
    if (!course_marks.is_open()) {
        std::cerr << "Error: The file could not be opened.\n"; // Use error output to tell user the file can't be opened
        return 1;
    }

    // Declare vectors to store the data read from the file 
    std::vector<double> mark; // Integer (decimal) vector for the student's mark
    std::vector<std::string> code; // String vector for the course code 
    std::vector<std::string> name; // String vector for the course name

    std::string line; // Declare string to hold a single line from the file 

    int record_count{0}; // Declare integer to count the number of records in the file

    // Read and store file data to the above defined vectori have a s
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
            std::cerr << "Error: The data from the file could not be read.\n"; // Use error output to tell user the data can't be read
            return 1;
        }

    }

    // Traverse and print all elements of the mark vector (by index)
    std::cout << "\nFull list of student marks:" << "\n";

    for (int index{0}; index < mark.size(); index++) { // Loops until all vector entries have been visited, increments index after each visit
        std::cout << mark[index] << " |" << name[index] << "\n"; // Outputs each mark entry to the user
    }

    std::cout << "Number of data entries (records): " << record_count << "\n"; // Output the number of records to the user 

    std::cout << "\nPlease select a year for which you wish to view the student marks. Enter a number (1-4): "; // Ask user to select a year to output marks for

    int chosen_year;
    std::cin >> chosen_year; // Declare variable to store user input for chosen year 

    std::vector<int> year; // Integer vector for the first number of the course code
    std::vector<double> year_mark; // Integer (double) vector for the marks for a specific year
    
    // Fill the year vector with the number first character of the course code 
    for (int index{0}; index < code.size(); index++) { 
        year.push_back(code[index][0] - '0'); // Subtract character zero because string characters stored as their ASCII values
    }

    // Traverse and print all elements of the mark for the chosen year
    std::cout << "\nFull list of student marks for Year " << chosen_year << ":\n";

    for (int index{0}; index < mark.size(); index++) {
        if (year[index] == chosen_year) {
            std::cout << mark[index] << " |" << name[index] << "\n"; // Outputs course codes from chosen year only
        }
    }

    // Fill the year_mark vector with the marks for that year
    for (int index{0}; index < mark.size(); index++) {
        if (year[index] == chosen_year) {
            year_mark.push_back(mark[index]);
        }
    }

    double year_mean{mean(year_mark, record_count)}; // Declare and define the year mean using mean function
    double year_sd{sd(year_mark, record_count, year_mean)}; // Declare and define the year standard deviation using sd function
    double year_se{se(year_sd, record_count)}; // Declare and define the year standard error using se function

    // Output the summary statistics for the given year
    std::cout << "\nSummary statistics for Year " << chosen_year << ":\n";
    std::cout << "Mean: " << year_mean << "\n";
    std::cout << "Standard deviation: " << year_sd << "\n";
    std::cout << "Standard error: " << year_se << "\n";

    return 0;
}
