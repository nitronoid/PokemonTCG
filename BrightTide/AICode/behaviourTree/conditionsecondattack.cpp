#include "conditionsecondattack.h"

conditionSecondAttack::conditionSecondAttack(int _currentEnergy, int _energy2)
{
    m_currentEnergy = _currentEnergy;
    m_energyNeeded = _energy2;
}
//-------------------------------------------------------------------
bool conditionSecondAttack::conditionFunction()
{
    // currently saying always do attack 2 or 1
    // need to change this soon because you can have the inbetween
    // what about if you have more energies attached on your card then you can't play
    // try to figure out how this work

    // temporary solution
    if(m_currentEnergy >= m_energyNeeded)
    {
        m_result = true;
    }
    return m_result;
}
