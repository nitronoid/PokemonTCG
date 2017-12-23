#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H
#include "bench.h"

class DamageCalculator
{
public:

    DamageCalculator()=default;
    DamageCalculator& operator =(const DamageCalculator &_original) = delete;

    //factor in weakness, bonus damages for active, factoring only bonus for benched
    void generalDamage(std::unique_ptr<std::array<Bench,2>> &_bench,
                       const unsigned &_turnCount,
                       const unsigned &_defenderIndex,
                       const unsigned &_damage);

    //factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon."
    void rawDamage(std::unique_ptr<std::array<Bench,2>> &_bench,
                   const unsigned &_turnCount,
                   const unsigned &_defenderIndex,
                   const unsigned &_damage);


    void increasePoison(const int _damage);
    void increaseBurn(const int _damage);
    void increaseConfuse(const int _damage);
    inline int getPoison() const { return m_poisonDamage; }
    inline int getBurn() const { return m_burnDamage; }
    inline int getConfuse() const { return m_confuseDamage; }

private:

    unsigned getAttacker(const unsigned _turnCount){return _turnCount % 2;}
    unsigned getDefender(const unsigned _turnCount){return (1+_turnCount) % 2;}


    int applyWeakRes(std::unique_ptr<std::array<Bench,2>> &_bench,
                     const unsigned &_turnCount);

    int applyBonusDamage(std::unique_ptr<std::array<Bench,2>> &_bench,
                         const unsigned &_turnCount,
                         const unsigned &_defenderIndex,
                         const PTCG::ORDER &_order);


    int m_weaknessMult = 2;
    int m_resistance = - 20;
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
};

#endif // DAMAGECALCULATOR_H
