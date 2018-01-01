#include "conditiondead.h"

conditionDead::conditionDead(int _health)
{
    m_health = _health;
}
//-------------------------------------------------------------------
bool conditionDead::conditionFunction()
{
    // checks if health is above zero (check if not dead)
    // should check if next turn my health is still above zero
    // future death
    if(m_health>1)
    {
        std::cout<<"WILL NOT BE DEAD SOON"<<'\n';
        m_result = true;
    }
    return m_result;
}
