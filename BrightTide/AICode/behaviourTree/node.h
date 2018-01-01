#ifndef NODE_H
#define NODE_H

#include <iostream>

// represents each node in the tree
class node
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    node() {;}
    ///-----------------------------------------------------------------
    /// @build run function virtual
    ///-----------------------------------------------------------------
    virtual bool run() = 0;
};

#endif // NODE_H
