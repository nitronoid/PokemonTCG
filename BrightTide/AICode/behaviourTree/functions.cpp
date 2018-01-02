#include "functions.h"

Functions::Functions()
{

}

bool Functions::needEnergy(int _currentEnergy, int _energyA0, int _energyA1)
{
    int m_totalEnergy = _energyA0 + _energyA1;
    if(_currentEnergy < m_totalEnergy)
    {
        std::cout<<"NEED ENERGY"<<'\n';
        m_result = true;
    }
    return m_result;
    m_result = false;
}

bool Functions::isDead(int _health)
{
    if(_health>0)
    {
        std::cout<<"WILL NOT BE DEAD SOON"<<'\n';
        m_result = true;
    }
    return m_result;
    m_result = false;
}

bool Functions::canAttack(int _currentEnergy, int _energy)
{
    if(_currentEnergy >= _energy)
    {
        m_result = true;
    }
    return m_result;
    m_result = false;
}

bool Functions::listEmpty(std::vector<Cards> _list)
{
    if(_list.size() != 0)
    {
        m_result = true;
    }
    return m_result;
    m_result = false;
}

bool Functions::addEnergy(Cards _card)
{
    _card.addEnergy();
    return true;
}
