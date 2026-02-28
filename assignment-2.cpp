// assignment-2.cpp
// PHYS30762 Assignment 2 - Course Marks Data
// Roman le Bon - 11423027

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
#include<iomanip>
#include<algorithm>

std::ifstream course_marks{"course_marks.dat"}; // Open and attatch data from course_marks.dat to course_marks (read only)

// Create function to calculate mean
double mean(const std::vector<double>& mark, int count) { // Pass in the mark vector (& insures it uses the original and doesn't make a new copy) as a constant, so it cannot be altered

    double sum_xi{0};

    for (int index{0}; index < mark.size(); index++) { // Loops until all vector entries have been visited, increments index after each visit
        sum_xi += mark[index]; // Adds individual mark to rolling sum
    }

    double mu{sum_xi / count};

    return mu;
  }

// Create function to calculate standard deviation 
double sd(const std::vector<double>& mark, int count, double mean) {

    double sxx{0};

    for (int index{0}; index < mark.size(); index++) {
        sxx += (mark[index] - mean) * (mark[index] - mean);
    }

    double sd{std::sqrt(sxx / (count - 1))};

    return sd;
}

// Create function to calculate standard error
double se(double sd, int count) {

    double se{sd/(std::sqrt(count))};

    return se;
}

int main() {

    std::cout << std::fixed << std::setprecision(1); // Ensures floating-point numbers are printed to console with 1dp for conistent output of marks

    // Check that the file is successfully opened, inform user if not 
    if (!course_marks.is_open()) {
        std::cerr << "\n* Error: The file could not be opened.";
        return 1;
    }

    // Declare variables to store the student's mark, course code and course name data from the file 
    std::vector<double> mark; 
    std::vector<std::string> code; 
    std::vector<std::string> name; 

    std::string line; // Declare string to hold a single line from the file 

    int record_count{0};

    // Read and store file data to the above defined vectors
    while (std::getline(course_marks, line)) {

        std::stringstream ss(line); // Create a stream from the line so we can extract and seperate the different data

        // Use temporary variables to store data from the single line
        double line_mark;
        std::string line_code;
        std::string line_name; 

        // Extract the data if formatted correctly 
        if (ss >> line_mark >> line_code) { 

            // Extracting course names is handled differently - handling them as above would only retrieve the first word
            std::getline(ss, line_name); // Extracts the rest of the string stream (including spaces)

            // If there is a valid name, containing an intial whitespace, we remove erase the first character (the space)
            if (!line_name.empty() && line_name[0] == ' ') {
                line_name.erase(0,1);
            }

            mark.push_back(line_mark);
            code.push_back(line_code);
            name.push_back(line_name); 

            record_count ++;

        }

        else {
            std::cerr << "\n* Error: The data from the file could not be read."; 
            return 1;
        }

    }

    // Check file is non-empty
    if (record_count == 0) {
        std::cerr << "\n* Error: The file contains no valid data.";
        return 1;
    }

    // Traverse and print all elements of the mark vector (by index)
    std::cout << "\nFull list of student marks:" << "\n";

    for (int index{0}; index < mark.size(); index++) {
        std::cout << mark[index] << " |" << name[index] << "\n"; // Outputs each mark entry to the user
    }

    std::cout << "Number of data entries (records): " << record_count << "\n"; // Output the number of records to the user 

    // Input validation for user input of the year to output marks for
    int chosen_year;
    bool valid_year = false;

    while (!valid_year) {

        std::cout << "\nPlease select a year for which you wish to view the student marks. Enter a number (1-4): "; // Ask user to select a year to output marks for

        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);

        // Ensure integer conversion is possible and that the number is between 1 and 4
        if (!(ss >> chosen_year) || chosen_year < 1 || chosen_year > 4) {
            std::cout << "\n-> Invalid input. Enter a number between 1 and 4.\n";
            continue;
        }

        // Check for extra invalid input after the number
        std::string extra;
        if (ss >> extra) {
            std::cout << "\n-> Invalid input. Enter only one number.\n";
            continue;
        }

        valid_year = true;
    }

    // Input validation for user input of whether to order courses alphabetically or not 
    char order_courses;
    bool valid_order = false;

    while (!valid_order) {

        std::cout << "\nPlease select if you wish to view the courses in (alphabetical) order. Enter either character (y/n): "; // Ask user if they want to sort output by course name

        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);

        // Ensure character conversion and that the character is either y or n
        if (!(ss >> order_courses) || (order_courses != 'y' && order_courses != 'n')) {
            std::cout << "\n-> Invalid input. Enter only 'y' or 'n'.\n";
            continue;
        }

        // Check for extra invalid input after the character
        std::string extra;
        if (ss >> extra) {
            std::cout << "\n-> Invalid input. Enter only one character.\n";
            continue;
        }

        valid_order = true;
    }

    // Declare variables to store the year (first number of the course code) and the index of a data entry, as well as the marks and course count for a specific year
    std::vector<int> indices;
    std::vector<int> year; 
    std::vector<double> year_mark;
    int year_count{0};
    
    // Store values in the year vector 
    for (int index{0}; index < code.size(); index++) { 
        year.push_back(code[index][0] - '0'); // Subtract character zero because string characters stored as their ASCII values
    }

    // Store index of each relevant course to indices vector
    for (int index{0}; index < mark.size(); index++ ) {
        if (year[index] == chosen_year) {
            indices.push_back(index);
        }
    }

    // Check that there are actually courses for the chosen year
    if (indices.empty()) {
            std::cerr << "\n* Error: No courses found for Year " << chosen_year << ".\n";
            return 1;
    }

    // Sort indices by course name if required by the user
    if (order_courses == 'y') {
        for (int i{0}; i < indices.size(); i++) {
            for (int j{i+1}; j < indices.size(); j++) {

                // Swap course names if the next (jth) course is 'less' (ASCII order) than the current (ith) course
                if (name[indices[j]] < name[indices[i]]) { // Case-sensitive alphabetical order (capitalisation differences in course names affects ordering)
                    std::swap(indices[i], indices[j]); 
                }
            }
        }
    }

    // Traverse and print all elements of the mark for the chosen year (sorted or unsorted)
    std::cout << "\nFull list of student marks for Year " << chosen_year << ":\n";

    for (int index{0}; index < indices.size(); index++) {
            std::cout << mark[indices[index]] << " |" << name[indices[index]] << "\n"; // Outputs course codes from chosen year only
            year_mark.push_back(mark[indices[index]]); // Store values in the year_mark vector 
            year_count++; // Use this loop to find the course_count
    }

    if (year_count < 2) {
        std::cerr << "\n* Error: Not enough data to calculate standard deviation.\n";
        return 1;
    }

    // Declare and define the year-specific summary statistics using the mean, standard deviation and standard error functions at the start of the program
    double year_mean{mean(year_mark, year_count)}; 
    double year_sd{sd(year_mark, year_count, year_mean)}; 
    double year_se{se(year_sd, year_count)}; 

    std::cout << std::fixed << std::setprecision(5); // Ensures floating-point numbers are printed to console with 5dp for conistent output of summary statistics

    // Output the summary statistics for the given year
    std::cout << "\nSummary statistics for Year " << chosen_year << ":\n";
    std::cout << "Mean: " << year_mean << "\n";
    std::cout << "Standard deviation: " << year_sd << "\n";
    std::cout << "Standard error: " << year_se << "\n";

    return 0;
}
 