#ifndef CONDITION_H
#define CONDITION_H

#include "node.h"
#include <iostream>
#include <chrono>
#include <thread>

class Condition : public node
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    Condition();
    ///-----------------------------------------------------------------
    /// @build run method
    ///-----------------------------------------------------------------
    virtual bool run() override;
    ///-----------------------------------------------------------------
    /// @build function condition
    ///-----------------------------------------------------------------
    virtual bool conditionFunction() = 0;
protected:
    ////-----------------------------------------------------------------
    /// @build status of the node
    ///-----------------------------------------------------------------
    bool m_result = false;
};

#endif // CONDITION_H
