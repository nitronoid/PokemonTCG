#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>


class Node
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Node() {;}
    ///------------------------------------------------------------------------------
    /// @build virtual execution function
    ///------------------------------------------------------------------------------
    virtual bool execute() = 0;
};

#endif // NODE_H
