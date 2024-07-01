#include "Course.h"

// Default constructor definition
Course::Course() : course_num(""), title(""), prerequisites({}) {}

// Parameterized constructor definition
Course::Course(const string& course_num, const string& title, const vector<string>& prerequisites)
    : course_num(course_num), title(title), prerequisites(prerequisites) {}

string Course::getCourseNum() const {
    return course_num;
}

string Course::getTitle() const {
    return title;
}

vector<string> Course::getPrerequisites() const {
    return prerequisites;
}
