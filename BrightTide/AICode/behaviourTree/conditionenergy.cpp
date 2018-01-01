#include "conditionenergy.h"

conditionEnergy::conditionEnergy(int _currentEnergy, int _energy1, int _energy2)
{
    m_currentEnergy = _currentEnergy;
    m_totalEnergy = _energy1 + _energy2;
}
//-------------------------------------------------------------------
bool conditionEnergy::conditionFunction()
{
    // need to check if there is energy
    if(m_currentEnergy < m_totalEnergy)
    {
        std::cout<<"NEED ENERGY"<<'\n';
        m_result = true;
    }
    return m_result;
}
