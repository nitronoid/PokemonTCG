#ifndef CONDITIONENERGY_H
#define CONDITIONENERGY_H

#include "condition.h"

class conditionEnergy : public Condition
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    conditionEnergy(int _currentEnergy, int _energy1, int _energy2);
    ///-----------------------------------------------------------------
    /// @build function condition overwritten
    ///-----------------------------------------------------------------
    virtual bool conditionFunction() override;
private:
    ///-----------------------------------------------------------------
    /// @build current energy of the card
    ///-----------------------------------------------------------------
    int m_currentEnergy;
    ///-----------------------------------------------------------------
    /// @build total energy of the card needed
    ///-----------------------------------------------------------------
    int m_totalEnergy;
};

#endif // CONDITIONENERGY_H
