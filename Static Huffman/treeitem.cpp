#include "treeitem.h"

TreeItem::TreeItem(char c, int w)
{
    this->symbol=c;
    this->weight=w;
}

bool
TreeItem::operator> (TreeItem ob)
{
    return this->weight>ob.weight;
}

bool
TreeItem::operator< (TreeItem ob)
{
    return this->weight<ob.weight;
}

int
TreeItem::getWeight()
{
    return this->weight;
}

char
TreeItem::getSymbol()
{
    return this->symbol;
}
