# CS300-ABCU-Advising-Program
CS 300 – Data Structures and Algorithms | Binary Search Tree implementation for ABCU's academic advising assistance program, with pseudocode and Big O runtime analysis for Vector, Hash Table, and BST data structures.

# CS 300 – Data Structures and Algorithms
## ABCU Advising Assistance Program

### Portfolio Submission – Module Eight Journal

---

## Project Overview

This repository contains the work completed for CS 300 at Southern New Hampshire University. The course focused on understanding and applying data structures and algorithms to solve real-world programming problems. The two projects in this course centered on building an advising assistance program for ABCU's Computer Science department — a tool that allows academic advisors to load, sort, search, and display course data efficiently.

- **Project One** – Pseudocode and runtime analysis comparing three data structures: Vector, Hash Table, and Binary Search Tree (BST).
- **Project Two** – A fully functional C++ command-line application using a Binary Search Tree to store, sort, and retrieve course information.

---

## Reflection

### What was the problem you were solving in the projects for this course?

The core problem was designing and implementing a software solution to help academic advisors at ABCU manage course information more effectively. Specifically, the program needed to accomplish two things: print a complete, alphanumerically sorted list of all Computer Science courses, and allow an advisor to look up any individual course and display its title along with all of its prerequisites. The challenge was not simply making the program work, but choosing the right data structure to make it work *efficiently* — one that could handle loading, sorting, and searching course data in a way that scales well as the number of courses grows.

---

### How did you approach the problem? Consider why data structures are important to understand.

My approach began with analysis before any coding. In Project One, I wrote pseudocode and performed Big O runtime analysis for three different data structures — a Vector, a Hash Table, and a Binary Search Tree — to compare how each would handle the required operations. Understanding data structures is critical because the choice of structure directly determines how well a program performs. A vector, for example, is simple and fast to load but requires O(n log n) sorting before printing and O(n) for each search. A hash table offers O(1) average-case lookups but provides no natural ordering, making alphanumeric sorting expensive. The Binary Search Tree struck the best balance: it maintains sorted order inherently through its structure, delivers O(log n) average-case search performance, and produces a perfectly sorted list through a simple in-order traversal in O(n) time. After completing this analysis, I chose the BST as the foundation for Project Two, which I then implemented in C++.

---

### How did you overcome any roadblocks you encountered while going through the activities or project?

One of the main challenges was handling edge cases in the CSV file parsing — specifically dealing with malformed lines, extra whitespace, inconsistent line endings, and missing fields. I addressed this by writing a dedicated `trim()` utility function and adding validation logic inside `loadDataStructure()` that skips blank lines and warns on any line missing both a course number and a course name. Another roadblock was ensuring that course lookups were case-insensitive, since advisors might type a course number in any combination of upper or lower case. I solved this by applying a `toUpperCase()` conversion both when inserting courses into the BST and when accepting user input for searches, so comparisons always happen on a normalized, uppercase key. Breaking the problem into focused, single-responsibility functions — loading, inserting, traversing, searching, and displaying — made it much easier to isolate and fix issues as they came up.

---

### How has your work on this project expanded your approach to designing software and developing programs?

This project reinforced the importance of designing before coding. Before writing a single line of C++ for Project Two, I had already mapped out the program's logic through pseudocode and understood its expected runtime characteristics. That upfront analysis made the implementation phase significantly smoother because the structure and intent of every function was already clear. It also deepened my understanding of how algorithmic choices ripple through a program — switching from a vector to a BST didn't just change one function; it changed how data was stored, how it was sorted, and how it was retrieved. That kind of systems-level thinking — seeing how each component interacts with the whole — is something I will carry into every future project.

---

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

Working through this project pushed me to be much more deliberate about code organization and naming. I applied consistent naming conventions throughout — `loadDataStructure`, `printCourseList`, `printCourse` — so that function names clearly communicate their purpose without needing to read the implementation. I used in-line comments at every logical boundary to explain the *why* behind decisions, not just the *what*. I also structured the BST class to keep its internal implementation details private and expose only a clean public interface, which means the underlying storage logic could be modified in the future without breaking the rest of the program. Input validation was built in from the start rather than added as an afterthought, making the program robust to real-world use. Together, these practices produced code that any future developer — or future me — could read, understand, and extend without difficulty.

---

## Repository Contents

| File | Description |
|------|-------------|
| `README.md` | Portfolio reflection and project overview |
| `ProjectTwo.cpp` | Project Two – Full C++ BST implementation of the ABCU Advising Program |
| `Project_One_Analysis.docx` | Project One – Pseudocode and Big O runtime analysis for Vector, Hash Table, and BST |

---

## How to Run the Program

1. Compile the source file using a C++ compiler:
   ```bash
   g++ -o ProjectTwo ProjectTwo.cpp
   ```
2. Run the compiled program:
   ```bash
   ./ProjectTwo
   ```
3. When prompted, enter the name of the CSV course data file (e.g., `CS_300_Advising_Program_Input.csv`).
4. Use the menu options to load data, print the course list, or look up a specific course.

---

*CS 300 – Data Structures and Algorithms | Southern New Hampshire University*
