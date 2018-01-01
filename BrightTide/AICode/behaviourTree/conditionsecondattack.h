#ifndef CONDITIONSECONDATTACK_H
#define CONDITIONSECONDATTACK_H

#include "condition.h"

/// NOTE: condition energy has the same lay out
class conditionSecondAttack : public Condition
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    conditionSecondAttack(int _currentEnergy, int _energy2);
    ///-----------------------------------------------------------------
    /// @build override
    ///-----------------------------------------------------------------
    virtual bool conditionFunction() override;
private:
    ///-----------------------------------------------------------------
    /// @build current energy of the card
    ///-----------------------------------------------------------------
    int m_currentEnergy;
    ///-----------------------------------------------------------------
    /// @build energy needed for attack
    ///-----------------------------------------------------------------
    int m_energyNeeded;
};

#endif // CONDITIONSECONDATTACK_H
