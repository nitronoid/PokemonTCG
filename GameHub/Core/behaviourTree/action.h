#ifndef ACTION_H
#define ACTION_H

#include "node.h"
#include <functional>

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

class testAction : public Action
{
public:
    testAction(){;}
    virtual bool execute() override;
private:
};



#endif // ACTION_H
