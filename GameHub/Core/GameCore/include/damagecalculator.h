#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H
#include "boardslot.h"

class damageCalculator
{
public:
    float GetTotal() const {return m_totalDamage;}
    float GetTotalNoBonus() const {return m_noBonus;}
    float UpdateDamage(std::unique_ptr<BoardSlot> _refSlot);
private:
    void Calculate();
    //std::unique_ptr<BoardSlot> m_refSlot;
    float m_noBonus;
    float m_totalDamage;
}

#endif // DAMAGECALCULATOR_H
