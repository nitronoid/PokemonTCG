#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H
#include "bench.h"

class DamageCalculator
{
public:
    DamageCalculator() = default;
    DamageCalculator(CalculateDamage &) = default;

    void applyDamage() const;
    //factor in weakness, bonus damages for active, factoring only bonus for benched
    void generalDamage(const unsigned &_id, const unsigned &damage) const;
    //factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon."
    void rawDamage(const unsigned &_id, const unsigned &_damage) const;

    void increasePoison(const int _damage);
    void increaseBurn(const _damage);
    void increaseConfuse(const _damage);

private:
    int applyWeakRes()const;
    int applyBonusDamage(const unsigned &_id, const PTCG::ORDER &_order)const;

    int m_weaknessMult = 2;
    int m_resistance = 20;
    int m_poisonDamage = 10;
    int m_burnDamage = 20;
    int m_confuseDamage = 30;





//    BASE + NULL         + WEAKNESS/RES   + NULL
//    BASE + BONUS        + WEAKNESS/RES   + NULL
//    BASE + WEAKNESS/RES + NULL           + NULL
//    BASE + WEAKNESS/RES + BONUS          + NULL
//    BASE + BONUS        + WEAKNESS/RES   + BONUS
//    BASE + BONUS        + NULL           + BONUS
//    BASE + NULL         + NULL           + NULL
}

#endif // DAMAGECALCULATOR_H
