#ifndef TREEITEM_H
#define TREEITEM_H

#include <memory>

class TreeItem
{
    int weight;
    char symbol;
public:
    std::shared_ptr<TreeItem> parent;
    std::shared_ptr<TreeItem> firstChild;
    std::shared_ptr<TreeItem> secondChild;

    TreeItem(char c, int w);
    bool operator> (TreeItem ob);
    bool operator< (TreeItem ob);
    int getWeight();
    char getSymbol();

};

#endif // TREEITEM_H
