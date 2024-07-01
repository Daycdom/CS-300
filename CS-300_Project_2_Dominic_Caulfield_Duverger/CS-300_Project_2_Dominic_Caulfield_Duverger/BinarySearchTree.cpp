#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    // Implement destructor to release allocated memory if needed
}

void BinarySearchTree::insert(const Course& course) {
    insertNode(root, course);
}

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

void BinarySearchTree::printInOrder() {
    printInOrderHelper(root);
}

void BinarySearchTree::printInOrderHelper(TreeNode* node) {
    if (node != nullptr) {
        printInOrderHelper(node->left);
        std::cout << "Course Number: " << node->course.course_num
            << ", Title: " << node->course.title
            << ", Prerequisites: ";
        for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
            std::cout << node->course.prerequisites[i];
            if (i != node->course.prerequisites.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        printInOrderHelper(node->right);
    }
}

Course* BinarySearchTree::findCourse(const string& course_num) {
    return findCourseHelper(root, course_num);
}

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
