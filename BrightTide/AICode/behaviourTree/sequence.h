#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "compositenode.h"
#include <chrono>
#include <thread>

class Sequence : public compositeNode
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    Sequence();
    ///-----------------------------------------------------------------
    /// @build run overwrite function
    ///-----------------------------------------------------------------
    virtual bool run() override;
};

#endif // SEQUENCE_H
