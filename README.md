# PHYS30762 – Assignment 2

## Highlights

- Reads structured course mark data from `course_marks.dat`
- Stores data using `std::vector` and `std::string`
- Computes mean, sample standard deviation, and standard error
- Filters courses by academic year (1–4)
- Optional alphabetical sorting
- Robust input validation using `std::getline` and `std::stringstream`
- Graceful error handling for all edge cases

## Overview

This program reads course mark data from a structured text file and performs statistical analysis on the marks.

Each record consists of:
- A numerical mark
- A course code
- A course name

The first digit of the course code determines the academic year.  
The user selects a year (1–4), and the program filters the data accordingly.  
For the selected year, the program calculates:

- Mean
- Sample standard deviation
- Standard error

The program is designed to handle invalid input and file errors safely.

## Usage

When executed:

1. The program reads and validates the input file.
2. The full list of marks is displayed.
3. The user selects an academic year (1–4).
4. The user chooses whether to sort courses alphabetically.
5. Filtered marks and summary statistics are displayed.

Example interaction:

```text
Please select a year (1-4): 2
Please select if you wish to view the courses in alphabetical order (y/n): y
```

## Implementation Details

### Data Storage

Course data is stored using standard containers:

```cpp
std::vector<double> mark;
std::vector<std::string> code;
std::vector<std::string> name;
```

Each line is parsed using `std::stringstream`:

```cpp
std::getline(course_marks, line);
std::stringstream ss(line);

if (ss >> line_mark >> line_code) {
    std::getline(ss, line_name);
}
```

### Statistical Calculations

Mean:

$$
\mu = \frac{1}{N} \sum x_i
$$

```cpp
for (int index{0}; index < mark.size(); index++) {
    sum_xi += mark[index];
}
```

Sample standard deviation:

$$
\sigma = \sqrt{\frac{1}{N-1} \sum (x_i - \mu)^2}
$$

```cpp
double sd{std::sqrt(sxx / (count - 1))};
```

Standard error:

$$
\sigma_\mu = \frac{\sigma}{\sqrt{N}}
$$

```cpp
double se{sd/(std::sqrt(count))};
```

### Filtering by Year

The academic year is extracted from the first digit of the course code:

```cpp
year.push_back(code[index][0] - '0');
```

Relevant courses are selected using:

```cpp
if (year[index] == chosen_year) {
    indices.push_back(index);
}
```

Alphabetical sorting is implemented by swapping indices:

```cpp
if (name[indices[j]] < name[indices[i]]) {
    std::swap(indices[i], indices[j]);
}
```

## Error Handling

The program terminates safely in the following cases:

- File fails to open
- Incorrect file formatting
- Empty file
- Invalid year input
- Invalid y/n input
- No courses found for selected year
- Fewer than two entries for standard deviation

Input validation is implemented using:

```cpp
std::getline(std::cin, input);
std::stringstream ss(input);
```

Graceful termination is performed using:

```cpp
return 1;
```

## Compilation

Tested using g++11 as required.

Compile:

```bash
g++ -std=c++11 assignment-2.cpp -o assignment-2
```

Run:

```bash
./assignment-2
```

## Development Process

The program was developed incrementally, with each major feature committed separately to GitHub. The commit history reflects the following progression:

1. Opened the input file and validated that it opened successfully.
2. Read and parsed the data from the file into `std::vector` containers.
3. Counted and output the number of data entries.
4. Printed the full list of student marks.
5. Implemented the function to calculate the mean.
6. Implemented the function to calculate the standard deviation.
7. Implemented the function to calculate the standard error.
8. Added the ability to output marks for a user-specified year.
9. Added summary statistics for the selected year.
10. Implemented optional alphabetical ordering of courses.
11. Improved output formatting by fixing floating-point precision.
12. Strengthened input validation for year selection.
13. Strengthened input validation for alphabetical ordering.

Each stage was committed separately to demonstrate structured and incremental development.

## Author

Roman le Bon  
University of Manchester