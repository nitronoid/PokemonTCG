#include "cards.h"

Cards::Cards()
{
    m_type = 0;
    m_health = 70;
    m_energy_0 = 1;
    m_energy_1 = 2;
    m_attack_1 = 10;
    m_attack_2 = 20;
    m_currentEnergy = 0;
}
//-------------------------------------------------------------------
void Cards::setType(int _type)
{
    m_type = _type;
}
//-------------------------------------------------------------------
void Cards::setHealth(int _health)
{
    m_health = _health;
}
//-------------------------------------------------------------------
void Cards::setEnergy0(int _energy)
{
    m_energy_0 = _energy;
}
//-------------------------------------------------------------------
void Cards::setEnergy1(int _energy)
{
    m_energy_1 = _energy;
}
//-------------------------------------------------------------------
void Cards::setAttack0(int _attack)
{
    m_attack_1 = _attack;
}
//-------------------------------------------------------------------
void Cards::setAttack1(int _attack)
{
    m_attack_2 = _attack;
}
//-------------------------------------------------------------------
void Cards::setCurrentEnergy(int _currentEnergy)
{
    m_currentEnergy = _currentEnergy;
}
void Cards::addEnergy()
{
    m_currentEnergy++;
}

//-------------------------------------------------------------------
int Cards::getType()
{
    return m_type;
}
//-------------------------------------------------------------------
int Cards::getHealth()
{
    return m_health;
}
//-------------------------------------------------------------------
int Cards::getEnergy_0()
{
    return m_energy_0;
}
//-------------------------------------------------------------------
int Cards::getEnergy_1()
{
    return m_energy_1;
}
//-------------------------------------------------------------------
int Cards::getAttack_0()
{
    return m_attack_1;
}
//-------------------------------------------------------------------
int Cards::getAttack_1()
{
    return m_attack_2;
}
//-------------------------------------------------------------------
int Cards::getCurrentEnergy()
{
    return m_currentEnergy;
}
