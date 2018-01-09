#ifndef TREE_H
#define TREE_H

#include "sequence.h"
#include "selector.h"
#include "action.h"
#include "condition.h"

class Tree
{
public:
    /// @build default constructor to make behaviour tree
    /// maybe make another constructor
    Tree();
    /// @build function that runs the tree
    void runTree();
    /// @build function that constructucs tree
    void createTree();

private:
    /// @build root node
    Sequence* rootNode = new Sequence;

};

#endif // TREE_H
