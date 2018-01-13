#ifndef CONDITION_H
#define CONDITION_H

#include "node.h"


class Condition : public Node
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Condition();
    ///------------------------------------------------------------------------------
    /// @build execute override function
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
    ///------------------------------------------------------------------------------
    /// @build virtual bool condition function
    ///------------------------------------------------------------------------------
    virtual bool conditionFunction() = 0;
};

class energyCondition : public Condition
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    energyCondition(bool function);
    ///------------------------------------------------------------------------------
    /// @build virtual bool condition function
    ///------------------------------------------------------------------------------
    virtual bool conditionFunction() override;
private:
    bool m_result = false;
    bool m_function;
};

#endif // CONDITION_H
