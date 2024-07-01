#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "BinarySearchTree.h"

using namespace std;

void displayMenu() {
    cout << "Welcome to the Course Information System!" << endl;
    cout << "1. Load data from file" << endl;
    cout << "2. Print alphabetically sorted list of courses" << endl;
    cout << "3. Print course information and prerequisites" << endl;
    cout << "9. Exit" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Enter your choice: ";
}

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

unordered_map<string, Course> parse(const vector<string>& lines) {
    unordered_map<string, Course> course_dict;
    vector<string> course_nums;

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
        course_nums.push_back(course_num);
    }

    return course_dict;
}

BinarySearchTree createBST(const unordered_map<string, Course>& course_dict) {
    BinarySearchTree binarySearch;
    for (const auto& entry : course_dict) {
        binarySearch.insert(entry.second);
    }
    return binarySearch;
}

void printCourseInformation(BinarySearchTree& binarySearch) {
    binarySearch.printInOrder();
}

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
