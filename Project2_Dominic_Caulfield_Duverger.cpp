#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits> // for numeric_limits
using namespace std;

// Class representing a Course
class Course {
public:
    string course_num;
    string title;
    vector<string> prerequisites;

    // Constructors
    Course() : course_num(""), title(""), prerequisites({}) {}
    Course(const string& course_num, const string& title, const vector<string>& prerequisites)
        : course_num(course_num), title(title), prerequisites(prerequisites) {}

    // Getters
    string getCourseNum() const { return course_num; }
    string getTitle() const { return title; }
    vector<string> getPrerequisites() const { return prerequisites; }
};

// Class representing a TreeNode in the Binary Search Tree
class TreeNode {
public:
    Course course;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(const Course& course) : course(course), left(nullptr), right(nullptr) {}
};

// Class representing a Binary Search Tree of Courses
class BinarySearchTree {
private:
    TreeNode* root;

    // Private helper methods
    void insertNode(TreeNode*& node, const Course& course);
    void printInOrderHelper(TreeNode* node);
    Course* findCourseHelper(TreeNode* node, const string& course_num);

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Public methods
    void insert(const Course& course);
    void printInOrder();
    Course* findCourse(const string& course_num);
};

// Method to insert a course into the BST
void BinarySearchTree::insert(const Course& course) {
    insertNode(root, course);
}

// Recursive method to insert a course node into the BST
void BinarySearchTree::insertNode(TreeNode*& node, const Course& course) {
    if (node == nullptr) {
        node = new TreeNode(course);
    }
    else {
        if (course.course_num < node->course.course_num) {
            insertNode(node->left, course);
        }
        else {
            insertNode(node->right, course);
        }
    }
}

// Method to perform an in-order traversal of the BST and print courses
void BinarySearchTree::printInOrder() {
    printInOrderHelper(root);
}

// Recursive helper method to perform in-order traversal and print courses
void BinarySearchTree::printInOrderHelper(TreeNode* node) {
    if (node != nullptr) {
        printInOrderHelper(node->left);
        cout << "Course Number: " << node->course.course_num << ", Title: " << node->course.title;
        const auto& prereqs = node->course.prerequisites;
        if (!prereqs.empty()) {
            cout << ", Prerequisites: ";
            for (size_t i = 0; i < prereqs.size(); ++i) {
                cout << prereqs[i];
                if (i != prereqs.size() - 1) {
                    cout << ", ";
                }
            }
        }
        else {
            cout << ", No prerequisites.";
        }
        cout << endl;
        printInOrderHelper(node->right);
    }
}

// Method to find a course in the BST based on course number
Course* BinarySearchTree::findCourse(const string& course_num) {
    return findCourseHelper(root, course_num);
}

// Recursive helper method to find a course in the BST based on course number
Course* BinarySearchTree::findCourseHelper(TreeNode* node, const string& course_num) {
    if (node == nullptr || node->course.course_num == course_num) {
        return node != nullptr ? &(node->course) : nullptr;
    }

    if (course_num < node->course.course_num) {
        return findCourseHelper(node->left, course_num);
    }
    else {
        return findCourseHelper(node->right, course_num);
    }
}

// Method to display the main menu options
void displayMenu() {
    cout << "Welcome to the course planner" << endl;
    cout << "1. Load data from file" << endl;
    cout << "2. Print alphabetically sorted list of courses" << endl;
    cout << "3. Print course information and prerequisites" << endl;
    cout << "9. Exit" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Enter your choice: ";
}

// Function to load data from a CSV file into a vector of strings
vector<string> load(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File cannot be opened." << endl;
        return {};
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

// Function to parse the loaded CSV lines into a map of course objects
unordered_map<string, Course> parse(const vector<string>& lines) {
    unordered_map<string, Course> course_dict;

    for (const auto& line : lines) {
        istringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cerr << "Error: Each line must contain at least a course number and a title." << endl;
            return {};
        }

        string course_num = tokens[0];
        string course_title = tokens[1];
        vector<string> prerequisites(tokens.begin() + 2, tokens.end());

        Course course(course_num, course_title, prerequisites);
        course_dict[course_num] = course;
    }

    return course_dict;
}

// Function to create a Binary Search Tree from the parsed course data
BinarySearchTree createBST(const unordered_map<string, Course>& course_dict) {
    BinarySearchTree binarySearch;
    for (const auto& entry : course_dict) {
        binarySearch.insert(entry.second);
    }
    return binarySearch;
}

// Main function to execute the program
int main() {
    string filename = "CS-300_ABCU_Advising_Program_Input.csv";  // Update with your file path
    BinarySearchTree binarySearch;
    int choice = 0;

    do {
        displayMenu();
        while (!(cin >> choice)) {
            // If input is not an integer, clear the input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer choice: ";
        }
        switch (choice) {
        case 1: {
            vector<string> lines = load(filename);
            if (lines.empty()) {
                continue;
            }
            unordered_map<string, Course> course_dict = parse(lines);
            if (course_dict.empty()) {
                continue;
            }
            binarySearch = createBST(course_dict);
            cout << "Data loaded successfully." << endl;
            break;
        }
        case 2: {
            binarySearch.printInOrder();
            break;
        }
        case 3: {
            string course_num;
            cout << "Enter course number to view details: ";
            cin >> course_num;
            transform(course_num.begin(), course_num.end(), course_num.begin(), ::toupper);

            Course* course = binarySearch.findCourse(course_num);
            if (course) {
                cout << "Course Information:" << endl;
                cout << "Course Number: " << course->course_num << endl;
                cout << "Course Title: " << course->title << endl;
                if (!course->prerequisites.empty()) {
                    cout << "Prerequisites: ";
                    for (size_t i = 0; i < course->prerequisites.size(); ++i) {
                        cout << course->prerequisites[i];
                        if (i != course->prerequisites.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
                else {
                    cout << "No prerequisites." << endl;
                }
            }
            else {
                cout << "Course not found." << endl;
            }
            break;
        }
        case 9: {
            cout << "Exiting program." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 9);

    return 0;
}
