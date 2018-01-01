#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include "cards.h"

class Functions
{
public:
    ///---------------------------------------------------------------
    /// @build constructor
    ///---------------------------------------------------------------
    Functions();
    ///---------------------------------------------------------------
    /// @build function that checks if you need energy
    ///---------------------------------------------------------------
    bool needEnergy(int _currentEnergy, int _energyA0, int _energyA1);
    bool isDead(int _health);
    bool canAttack(int _currentEnergy, int _energy);
    bool listEmpty(std::vector<Cards> _list);

private:
    bool m_result;
};

#endif // FUNCTIONS_H
