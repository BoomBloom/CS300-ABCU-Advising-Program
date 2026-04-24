// ProjectTwo.cpp
// CS 300 - ABCU Advising Assistance Program
// Implements a Binary Search Tree (BST) to store, sort, and retrieve course data.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================
// Data Structure: Course
// Holds a course number, title, and list of prerequisites.
// ============================================================
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// ============================================================
// Data Structure: BST Node
// ============================================================
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// ============================================================
// Binary Search Tree class
// Courses are keyed by courseNumber (alphanumeric order).
// ============================================================
class BinarySearchTree {
private:
    Node* root;

    // Recursive insert helper
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        } else if (course.courseNumber > node->course.courseNumber) {
            node->right = insert(node->right, course);
        }
        // Duplicate course numbers are ignored
        return node;
    }

    // In-order traversal: visits nodes in ascending key order
    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        inOrder(node->right);
    }

    // Recursive search helper
    Node* search(Node* node, const string& courseNumber) const {
        if (node == nullptr) return nullptr;
        if (courseNumber == node->course.courseNumber) return node;
        if (courseNumber < node->course.courseNumber) return search(node->left, courseNumber);
        return search(node->right, courseNumber);
    }

    // Recursive destructor helper
    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(Course course) {
        root = insert(root, course);
    }

    // Print all courses alphanumerically via in-order traversal
    void printCourseList() const {
        if (root == nullptr) {
            cout << "No courses loaded. Please load the data structure first." << endl;
            return;
        }
        cout << "\nHere is a sample schedule:\n" << endl;
        inOrder(root);
        cout << endl;
    }

    // Search and print a single course with its prerequisites
    void printCourse(const string& courseNumber) const {
        Node* result = search(root, courseNumber);
        if (result == nullptr) {
            cout << "Course " << courseNumber << " not found." << endl;
            return;
        }
        cout << result->course.courseNumber << ", " << result->course.courseName << endl;
        if (result->course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < result->course.prerequisites.size(); ++i) {
                if (i > 0) cout << ", ";
                // Look up the prerequisite name for a friendlier display
                Node* prereqNode = search(root, result->course.prerequisites[i]);
                if (prereqNode != nullptr) {
                    cout << prereqNode->course.courseNumber;
                } else {
                    cout << result->course.prerequisites[i];
                }
            }
            cout << endl;
        }
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

// ============================================================
// Utility: Convert string to uppercase
// Used so course number lookups are case-insensitive.
// ============================================================
string toUpperCase(const string& str) {
    string upper = str;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;
}

// ============================================================
// Utility: Trim leading/trailing whitespace from a string
// ============================================================
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end   = str.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return str.substr(start, end - start + 1);
}

// ============================================================
// Load CSV: Parses the course data file into the BST.
// Each line format: courseNumber,courseName[,prereq1,prereq2,...]
// ============================================================
void loadDataStructure(const string& filename, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file \"" << filename << "\". "
             << "Please check the file name and try again." << endl;
        return;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;  // skip blank lines

        stringstream ss(line);
        string token;
        vector<string> fields;

        // Split line by comma
        while (getline(ss, token, ',')) {
            token = trim(token);
            if (!token.empty()) {
                fields.push_back(token);
            }
        }

        // A valid course entry needs at least courseNumber and courseName
        if (fields.size() < 2) {
            cout << "Warning: Skipping malformed line: " << line << endl;
            continue;
        }

        Course course;
        course.courseNumber = toUpperCase(fields[0]);
        course.courseName   = fields[1];

        // Any remaining fields are prerequisites
        for (size_t i = 2; i < fields.size(); ++i) {
            course.prerequisites.push_back(toUpperCase(fields[i]));
        }

        bst.insert(course);
        ++count;
    }

    file.close();
    cout << count << " courses loaded successfully." << endl;
}

// ============================================================
// Display the main menu
// ============================================================
void displayMenu() {
    cout << "\n  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << "\nWhat would you like to do? ";
}

// ============================================================
// main()
// ============================================================
int main() {
    BinarySearchTree bst;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();

        // Validate that input is an integer
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore(1000, '\n');  // flush remainder of input line

        switch (choice) {
            case 1: {
                // Option 1: Load data from file
                string filename;
                cout << "Enter the file name to load: ";
                getline(cin, filename);
                filename = trim(filename);
                loadDataStructure(filename, bst);
                break;
            }

            case 2: {
                // Option 2: Print sorted course list
                if (bst.isEmpty()) {
                    cout << "No data loaded. Please select option 1 to load the data structure first." << endl;
                } else {
                    bst.printCourseList();
                }
                break;
            }

            case 3: {
                // Option 3: Print individual course info
                if (bst.isEmpty()) {
                    cout << "No data loaded. Please select option 1 to load the data structure first." << endl;
                } else {
                    string courseNum;
                    cout << "What course do you want to know about? ";
                    getline(cin, courseNum);
                    courseNum = toUpperCase(trim(courseNum));
                    bst.printCourse(courseNum);
                }
                break;
            }

            case 9: {
                // Option 9: Exit
                cout << "\nThank you for using the course planner!" << endl;
                break;
            }

            default: {
                // Any other input
                cout << choice << " is not a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}
