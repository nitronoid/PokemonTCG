#ifndef CONDITIONDEAD_H
#define CONDITIONDEAD_H

#include "condition.h"

class conditionDead : public Condition
{
public:
    ///-----------------------------------------------------------------
    /// @build a dead constructor
    ///-----------------------------------------------------------------
    conditionDead(int _health);
    ///-----------------------------------------------------------------
    /// @build condition overwrite
    ///-----------------------------------------------------------------
    virtual bool conditionFunction() override;
private:
    ///-----------------------------------------------------------------
    /// @build the health of the card (pokemon)
    ///-----------------------------------------------------------------
    int m_health;

};

#endif // CONDITIONDEAD_H
