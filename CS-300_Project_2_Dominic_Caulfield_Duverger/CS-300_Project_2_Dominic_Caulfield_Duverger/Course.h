#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

using namespace std;

class Course {
public:
    string course_num;
    string title;
    vector<string> prerequisites;

    // Default constructor
    Course();

    // Parameterized constructor
    Course(const string& course_num, const string& title, const vector<string>& prerequisites);
    string getCourseNum() const;
    string getTitle() const;
    vector<string> getPrerequisites() const;
};

#endif // COURSE_H
