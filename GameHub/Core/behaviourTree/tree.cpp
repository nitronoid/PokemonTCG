#include "tree.h"

Tree::Tree()
{

}

void Tree::runTree()
{
    while(!rootNode->execute())
        std::cout<<"returned false, stop"<<'\n';
}

void Tree::createTree()
{
    rootNode->addChild(new Action);
}
