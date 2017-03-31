#include "binarytree.h"

using namespace std;

BinaryTree::BinaryTree(vector<int> symbolsCount)
{
    list<shared_ptr<TreeItem>> forest=makeForest(symbolsCount); //создаем исходный лес
    while (forest.size()!=1)                                    //пока не в лесу не останется 1 дерево
    {
        list<shared_ptr<TreeItem>>::iterator min1=forest.begin();   //ищем 1 минимальный вес
        list<shared_ptr<TreeItem>>::iterator cur;
        for (cur=forest.begin();cur!=forest.end();++cur)
        {
            if (**cur<**min1)
            {
                min1=cur;
            }
        }
        list<shared_ptr<TreeItem>>::iterator min2=forest.begin();   //ищем 2 минимальный вес
        if (min2==min1)
        {
            min2++;
        }
        for (cur=forest.begin();cur!=forest.end();++cur)
        {
            if (**cur<**min2 && cur!=min1)
            {
                min2=cur;
            }
        }
        int w=min1->get()->getWeight()+min2->get()->getWeight();    //складываем весы
        TreeItem* item=new TreeItem(char(0),w);      //объединяем найденные деревья в одно
        shared_ptr<TreeItem> ptr(item);
        item->firstChild=*min1;             //ставим новому дереву 1 потомка
        item->secondChild=*min2;            //ставим новому дереву 2 потомка
        min1->get()->parent=ptr;            //ставим новое дерево родителем 1 потомку
        min2->get()->parent=ptr;            //ставим новое дерево родителем 1 потомку
        forest.erase(min1);                 //удаляем два этих дерева из списка
        forest.erase(min2);
        forest.push_front(shared_ptr<TreeItem>(item));  //добавляем в список новой дерево
    }
    this->root=forest.front();  //забираем из списка единственное (готовое) дерево
    forest.pop_front(); //ну и выкидываем его тоже из списка
}

map<char,string>
BinaryTree::getEncoding() const
{
    map<char,string> encoding;
    string currentPath;
    shared_ptr<TreeItem> currentItem=this->root;        //топаем в корень дерева

    while (currentItem.get()->firstChild || currentItem.get()->secondChild) //пока не упремся
    {
        while (currentItem.get()->firstChild)       //спускаемся по самой левой ветке до упора
        {
            currentPath.push_back('0');             //и кидаем в путь нули при каждом переходе
            currentItem=currentItem.get()->firstChild;
        }
        if (currentItem.get()->secondChild)         //теперь если можем идти вправо
        {
            currentPath.push_back('1');         //добавляем метку пути
            currentItem=currentItem.get()->secondChild; //идем в правого
        }
    }

    while (currentItem)                     //пока не обошли все дерево
    {
        if (!currentItem.get()->firstChild && !currentItem.get()->secondChild)
        {                                                                   //если мы в тупике
            encoding.insert(std::pair<char,string>(currentItem.get()->getSymbol(),currentPath));    //то выписываем символ и путь
            currentItem=currentItem.get()->parent;                          //переходим к родителю
            continue;
        }
        else                                            //если есть куда идти
        {
            char temp=currentPath.back();               //то получаем метку, откуда мы пришли
            currentPath.pop_back();                     //убираем её из пути
            if (temp=='1')                              //если мы пришли с правого потомка
            {
                currentItem=currentItem.get()->parent;  //то идем к родителю
            }
            if (temp=='0')                              //если с левого, то
            {
                if (currentItem.get()->secondChild)     //если можем иди в правого
                {
                    while (currentItem.get()->firstChild || currentItem.get()->secondChild) //пока не уперлись
                    {
                        if (currentItem.get()->secondChild) //если можем идти вправо
                        {
                            currentPath.push_back('1');         //добавляем метку пути
                            currentItem=currentItem.get()->secondChild; //идем в правого
                        }
                        while (currentItem.get()->firstChild)       //теперь, пока можем
                        {
                            currentPath.push_back('0');             //и кидаем в путь нули при каждом переходе
                            currentItem=currentItem.get()->firstChild;  //спускаемся по самой левой ветке до упора
                        }
                    }
                    continue;
                }
                else                                    //если вправо не можем идти
                {
                    currentItem=currentItem.get()->parent;  //идем в родителя
                }
            }
        }
    }
    return encoding;    //возвращаем полученный map (новую кодировку)
}

list<shared_ptr<TreeItem>>
BinaryTree::makeForest(vector<int> vec)
{
    list<shared_ptr<TreeItem>> itemsList;
    for (int i=0;i<256;i++)
    {
        TreeItem* item=new TreeItem(char(i),vec[i]);
        itemsList.push_back(shared_ptr<TreeItem>(item));
    }
    return itemsList;
}

std::shared_ptr<TreeItem>
BinaryTree::getRoot() const
{
    return root;
}
