#ifndef CONDITION_H
#define CONDITION_H

#include "node.h"
#include "cards.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

class Condition : public node
{
public:
    ///-----------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------
    Condition();
    ///-----------------------------------------------------------------
    /// @build run method
    ///-----------------------------------------------------------------
    virtual bool run() override;
    ///-----------------------------------------------------------------
    /// @build function condition
    ///-----------------------------------------------------------------
    virtual bool conditionFunction() = 0;
protected:
    ////-----------------------------------------------------------------
    /// @build status of the node
    ///-----------------------------------------------------------------
    bool m_result = false;
};
//-------------------------------------------------------------------
class conditionDead : public Condition
{
public:
    conditionDead(int _health);
    virtual bool conditionFunction() override;

private:
    int m_health;
};
//-------------------------------------------------------------------
class conditionAttack : public Condition
{
public:
    conditionAttack(int _currentEnergy, int _energyNeeded);
    virtual bool conditionFunction() override;
private:
    int m_currentEnergy;
    int m_energyNeeded;
};
//-------------------------------------------------------------------
class conditionListEmpty : public Condition
{
public:
    conditionListEmpty(std::vector<Cards> _listOfCards);
    virtual bool conditionFunction() override;
private:
    std::vector<Cards> m_list;
};
//-------------------------------------------------------------------
class conditionEnergy : public Condition
{
public:
    conditionEnergy(int _currentEnergy, int _energy1, int _energy2);
    virtual bool conditionFunction() override;
private:
    int m_currentEnergy;
    int m_totalEnergy;
};

#endif // CONDITION_H
