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
    Action(bool _action);
    ///------------------------------------------------------------------------------
    /// @build execution node override
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
private:
    bool m_action;

};



#endif // ACTION_H
