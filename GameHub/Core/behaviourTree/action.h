#ifndef ACTION_H
#define ACTION_H

#include "node.h"

class Action : public Node
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Action();
    ///------------------------------------------------------------------------------
    /// @build execution node override
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
};

#endif // ACTION_H
