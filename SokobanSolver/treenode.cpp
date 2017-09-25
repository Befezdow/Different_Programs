#include "treenode.h"
#include <unistd.h>
#include <stack>
#include <iostream>

TreeNode::TreeNode(DynamicField f, TreeNode *p):
    field(f),
    parent(p)
{}

void
TreeNode::printWinnerWay()
{
    const TreeNode* cur=this;                       //инициализируем текущий указатель
    std::stack<DynamicField> stk;                   //создаем временный стэк

    while (cur)                                     //пока не корень
    {
        stk.push(cur->getField());                  //засовываем поле в стэк
        cur=cur->getParent();                       //идем выше
    }

    int count=0;                                    //счетчик хода
    while (!stk.empty())                            //пока не выкинем все поля
    {
        system("clear");                            //числим экран
        std::cout<<"Ход №"<<count<<std::endl;       //пишем номер хода
        stk.top().print();                          //пишем поле
        stk.pop();                                  //выкидываем его из стека
        usleep(200000);                             //спим 0.2 секунды для анимации
        count++;                                    //увеличиваем ход
    }
    std::cout<<"Done!"<<std::endl;
}

DynamicField
TreeNode::getField() const
{
    return field;
}

const TreeNode*
TreeNode::getParent() const
{
    return parent;
}
