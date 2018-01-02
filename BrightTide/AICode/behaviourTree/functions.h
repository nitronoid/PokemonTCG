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
    /// @build CONDITION FUNCTION
    ///---------------------------------------------------------------
    /// @build function that checks if you need energy
    ///---------------------------------------------------------------
    bool needEnergy(int _currentEnergy, int _energyA0, int _energyA1);
    /// @build checks if the card is still alive
    bool isDead(int _health);
    /// @build see if it can attack (choose attack 1 or two or none)
    bool canAttack(int _currentEnergy, int _energy);
    /// @build checks if the list (bench, deck) is empty
    bool listEmpty(std::vector<Cards> _list);



    /// @build ACTION FUNCTION
    bool addEnergy(Cards _card);
private:
    bool m_result = false;
};

#endif // FUNCTIONS_H
