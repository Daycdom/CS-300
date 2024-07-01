#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <string>
#include <unordered_map>

class BinarySearchTree {
private:
    TreeNode* root;

    void insertNode(TreeNode*& node, const Course& course);
    void printInOrderHelper(TreeNode* node);
    Course* findCourseHelper(TreeNode* node, const string& course_num);

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(const Course& course);
    void printInOrder();
    Course* findCourse(const string& course_num);
};

#endif // BINARYSEARCHTREE_H
