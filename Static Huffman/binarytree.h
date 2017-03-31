#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "treeitem.h"
#include <list>
#include <vector>
#include <map>
#include <string>

class BinaryTree
{
    std::shared_ptr<TreeItem> root;
public:
    BinaryTree(std::vector<int> symbolsCount);
    std::map<char,std::string> getEncoding() const;
    static std::list<std::shared_ptr<TreeItem>> makeForest(std::vector<int> vec);
    std::shared_ptr<TreeItem> getRoot() const;
};

#endif // BINARYTREE_H
