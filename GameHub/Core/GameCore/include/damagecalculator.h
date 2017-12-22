#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H
#include "boardslot.h"

class DamageCalculator
{
public:
    int GetTotal() const {return m_totalDamage;}
    int GetTotalNoBonus() const {return m_noBonus;}
    int CalculateDamage(std::unique_ptr<BoardSlot> _refSlot, const unsigned _id, bool _includeWeakRes);
private:
    int CalcDmgWeakRes();
    int CalcDmgNoWeakRes();

    int m_noBonus = 0;
    int m_withBonus = 0;
    int m_totalDamage = 0;
    int m_noWeakRes = 0; // before applying weakness or resistance
    int m_withWeakRes = 0;  // after



//    BASE + NULL         + WEAKNESS/RES   + NULL
//    BASE + BONUS        + WEAKNESS/RES   + NULL
//    BASE + WEAKNESS/RES + NULL           + NULL
//    BASE + WEAKNESS/RES + BONUS          + NULL
//    BASE + BONUS        + WEAKNESS/RES   + BONUS
//    BASE + BONUS        + NULL           + BONUS
//    BASE + NULL         + NULL           + NULL
}

#endif // DAMAGECALCULATOR_H
