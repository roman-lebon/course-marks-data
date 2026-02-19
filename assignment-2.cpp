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

std::ifstream course_marks{"course_marks.dat"}; // Open and attatch data from course_marks.dat to course_marks (read only)

// Create function to calculate mean
double mean(const std::vector<double>& mark, int record_count) { // Pass in the mark vector (& insures it uses the original and doesn't make a new copy) as a constant, so it cannot be altered

    double sum_xi{0};

    for (int index{0}; index < mark.size(); index++) { // Loops until all vector entries have been visited, increments index after each visit
        sum_xi += mark[index]; // Adds individual mark to rolling sum
    }

    double mu{sum_xi / record_count};

    return mu;
  }

// Create function to calculate standard deviation 
double sd(const std::vector<double>& mark, int record_count, double mean) {

    double sxx{0};

    for (int index{0}; index < mark.size(); index++) {
        sxx += (mark[index] - mean) * (mark[index] - mean);
    }

    double sd{std::sqrt(sxx / (record_count - 1))};

    return sd;
  }

// Create function to calculate standard error
double se(double sd, int record_count) {

    double se{sd/(std::sqrt(record_count))};

    return se;
  }

int main() {

    std::cout << std::fixed << std::setprecision(1); // Ensures floating-point numbers are printed to console with 1dp for conistent output of marks

    // Check that the file is successfully opened, inform user if not 
    if (!course_marks.is_open()) {
        std::cerr << "Error: The file could not be opened.\n";
        return 1;
    }

    std::vector<double> mark; // Integer (decimal) vector for the student's mark
    std::vector<std::string> code; // String vector for the course code 
    std::vector<std::string> name; // String vector for the course name

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
            std::cerr << "Error: The data from the file could not be read.\n"; 
            return 1;
        }

    }

    // Traverse and print all elements of the mark vector (by index)
    std::cout << "\nFull list of student marks:" << "\n";

    for (int index{0}; index < mark.size(); index++) {
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

    std::cout << std::fixed << std::setprecision(5); // Ensures floating-point numbers are printed to console with 5dp for conistent output of summary statistics

    // Output the summary statistics for the given year
    std::cout << "\nSummary statistics for Year " << chosen_year << ":\n";
    std::cout << "Mean: " << year_mean << "\n";
    std::cout << "Standard deviation: " << year_sd << "\n";
    std::cout << "Standard error: " << year_se << "\n";

    return 0;
}
 