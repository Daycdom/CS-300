#ifndef TREENODE_H
#define TREENODE_H

#include "Course.h"

class TreeNode {
public:
    Course course;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Course& course);
};

#endif // TREENODE_H
