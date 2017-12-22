#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H
#include "bench.h"

class DamageCalculator
{
public:
    DamageCalculator() = default;
    DamageCalculator(CalculateDamage &) = default;

    void applyDamage() const {return m_totalDamage;}
    int applyBonusDamage() {return m_noBonus;}
    int calculateDamage(const unsigned _id, const unsigned _damage);
    int dealRawDamage(const unsigned _id, const unsigned _damage);

private:

    enum class ORDER {BEFORE, AFTER};
    int applyWeakRes();
    int applyBonusDamage();

    int m_weaknessMult = 2;
    int m_resistance = 20;





//    BASE + NULL         + WEAKNESS/RES   + NULL
//    BASE + BONUS        + WEAKNESS/RES   + NULL
//    BASE + WEAKNESS/RES + NULL           + NULL
//    BASE + WEAKNESS/RES + BONUS          + NULL
//    BASE + BONUS        + WEAKNESS/RES   + BONUS
//    BASE + BONUS        + NULL           + BONUS
//    BASE + NULL         + NULL           + NULL
}

#endif // DAMAGECALCULATOR_H
