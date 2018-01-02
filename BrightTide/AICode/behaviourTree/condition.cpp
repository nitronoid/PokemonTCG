#include "condition.h"

Condition::Condition()
{
}
//-------------------------------------------------------------------
bool Condition::run()
{
    // you should make a method that returns a condition
    // if certain condition returns true return true
    // else return false
    // to make them think
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    // return condition
    return conditionFunction();
}
//-------------------------------------------------------------------
conditionDead::conditionDead(int _health)
{
    m_health = _health;
}
//-------------------------------------------------------------------
bool conditionDead::conditionFunction()
{
    if(m_health>1)
    {
        std::cout<<"WILL NOT BE DEAD SOON"<<'\n';
        m_result = true;
    }
    return m_result;
}
//-------------------------------------------------------------------
conditionAttack::conditionAttack(int _currentEnergy, int _energyNeeded)
{
    m_currentEnergy = _currentEnergy;
    m_energyNeeded = _energyNeeded;
}
//-------------------------------------------------------------------
bool conditionAttack::conditionFunction()
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
//-------------------------------------------------------------------
conditionListEmpty::conditionListEmpty(std::vector<Cards> _listOfCards)
{
    m_list = _listOfCards;
}
//-------------------------------------------------------------------
bool conditionListEmpty::conditionFunction()
{
    if(m_list.size()!=0)
    {
        m_result = true;
    }
    return m_result;
}
//-------------------------------------------------------------------
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
