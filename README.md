# Student Management System

## Overview

The Student Management System is a console-based application developed in C++ to manage student records in an efficient and structured way. It allows users to perform core database operations such as adding, updating, deleting, searching, and viewing student information.

The system ensures data integrity through input validation, fast access using indexing, and persistent storage using file handling, making it reliable for real-world usage scenarios.

---

## Objectives

* To design a system for managing student records efficiently
* To implement CRUD operations using C++
* To ensure data persistence using file handling
* To optimize data retrieval using indexing techniques
* To apply Object-Oriented Programming concepts in a real-world project

---

## Features

* Add new student records with validation
* Update existing student details dynamically
* Delete records with confirmation
* Search records by name
* Display individual student details
* View all records in a formatted table
* Generate basic statistics (GPA, age, distribution)
* Automatic ID generation
* Timestamp tracking (created and updated)
* Persistent data storage using file system

---

## System Design

### Data Structure

Each student record contains:

* ID
* Name
* Email
* Age
* Semester
* GPA
* Course
* Created Date
* Last Updated

### Core Components

* Vector to store all student records
* Unordered Map (Hash Index) for fast lookup using student ID
* File Handling to save and load data
* Validation functions to ensure correct user input

---

## Functional Modules

### 1. Add Student

* Generates unique student ID
* Validates all inputs
* Stores record in memory and file

### 2. Update Student

* Finds record using ID
* Allows selective field updates
* Updates timestamp automatically

### 3. Delete Student

* Searches by ID
* Confirms before deletion
* Rebuilds index after removal

### 4. View Student

* Displays full details of a specific student

### 5. Display All Records

* Shows all students in a structured table format

### 6. Search

* Search students by name with partial match

### 7. Statistics

* Average GPA
* Minimum and maximum GPA
* Average age
* Semester-wise distribution
* Course-wise distribution

---

## Technologies Used

* C++
* STL (Vector, Unordered Map)
* File Handling (ifstream, ofstream)
* Object-Oriented Programming

---

## How to Run

### Compile

```bash
g++ main.cpp -o student_system
```

### Execute

```bash
./student_system
```

---

## Project Structure

```
Student-Management-System/
 ┣ main.cpp
 ┣ student_database.dat
 ┗ README.md
```

---

## Data Storage

* Data is stored in student_database.dat
* Uses delimiter-based serialization (|)
* Automatically loads data on startup
* Saves data on exit

---

## Key Highlights

* Efficient data retrieval using hash indexing
* Robust input validation system
* Scalable design supporting large datasets
* Clean and modular code structure
* Real-time statistics generation

---

## Limitations

* Console-based interface
* Limited search filters
* Single-user system

---

## Future Enhancements

* Graphical user interface
* Database integration (MySQL or SQLite)
* Advanced search filters
* Authentication system
* Multi-user support

---

## Output Screenshots

1. Main Menu Interface

Displays the primary navigation menu with all available operations such as adding, updating, deleting, viewing, and analyzing student records.

<img width="950" height="790" alt="image" src="https://github.com/user-attachments/assets/514f3c22-81d8-4f42-9927-52338ca14528" />

2. Adding a New Student

Shows the process of entering student details with proper input validation for fields like name, email, age, semester, GPA, and course.

<img width="815" height="769" alt="image" src="https://github.com/user-attachments/assets/88ae1ffd-5e63-4f0d-9aa5-f47da4d3c118" />

3. Viewing All Records

Displays all stored student records in a well-structured tabular format including ID, name, email, GPA, and course details.

<img width="951" height="797" alt="image" src="https://github.com/user-attachments/assets/e5051a65-11eb-44e4-a619-12d427c5ab75" />

4. Searching Student Records

Demonstrates searching functionality using student name with partial match support.

<img width="692" height="789" alt="image" src="https://github.com/user-attachments/assets/67a8ea5d-d853-4f61-9760-676abad27baf" />

5. Updating Student Details

Illustrates how existing student information can be modified with selective field updates.

<img width="738" height="827" alt="image" src="https://github.com/user-attachments/assets/61a4e8b7-4af4-48f1-be0d-da56732b9cc0" />

6. Deleting a Record

Shows the deletion process with confirmation prompt to prevent accidental data loss.

<img width="698" height="819" alt="image" src="https://github.com/user-attachments/assets/77899bb9-f6e1-407b-9bf9-3221185dd113" />

7. Statistics Dashboard

Provides insights such as average GPA, age distribution, and course-wise and semester-wise analysis.

<img width="757" height="804" alt="image" src="https://github.com/user-attachments/assets/e4ffd94d-7de4-42eb-9dad-f5f4204eaa66" />


## Conclusion

This project demonstrates the practical implementation of data structures, file handling, and object-oriented programming in C++. It provides a strong foundation for developing more advanced management systems.
