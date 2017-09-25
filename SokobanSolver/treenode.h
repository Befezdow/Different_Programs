#ifndef TREE_H
#define TREE_H

#include "field.h"

class TreeNode
{
    DynamicField field;             //поле узла
    TreeNode* parent;               //указатель на узла-родителя

public:
    TreeNode(DynamicField f, TreeNode* p);

    void printWinnerWay();          //напечатать последовательность ходов

    DynamicField getField() const;
    const TreeNode *getParent() const;
};

#endif // TREE_H
