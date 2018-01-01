#ifndef SELECTOR_H
#define SELECTOR_H

#include "compositenode.h"
#include <chrono>
#include <thread>

class Selector : public compositeNode
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    Selector();
    ///-----------------------------------------------------------------
    /// @build overwrite the function
    ///-----------------------------------------------------------------
    virtual bool run() override;
};

#endif // SELECTOR_H
