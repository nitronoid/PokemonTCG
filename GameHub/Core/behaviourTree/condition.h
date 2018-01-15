#ifndef CONDITION_H
#define CONDITION_H

#include "node.h"


class Condition : public Node
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Condition(bool _function);
    ///------------------------------------------------------------------------------
    /// @build execute override function
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
private:
    bool m_function;
};


#endif // CONDITION_H
