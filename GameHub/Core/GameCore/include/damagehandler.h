#ifndef DAMAGEHANDLER_H
#define DAMAGEHANDLER_H
#include "bench.h"

class DamageHandler
{
public:

    DamageHandler()=default;
    DamageHandler& operator =(const DamageHandler &_original) = delete;

    bool heal(Bench &_bench,
              const unsigned &_benchIndex,
              const unsigned &_value);

    //factor in weakness, bonus damages for active, factoring only bonus for benched
    void generalDamage(std::array<Bench, 2> &_bench,
                       const unsigned &_turnCount,
                       const unsigned &_defenderIndex,
                       const unsigned &_damage);

    //factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon from special conditions, attacks."
    void rawDamage(Bench &_bench,
                   const unsigned &_defenderIndex,
                   const unsigned &_damage);


    void increasePoison(const int _damage);
    void increaseBurn(const int _damage);
    void increaseConfuse(const int _damage);
    inline unsigned getPoison() const { return m_poisonDamage; }
    inline unsigned getBurn() const { return m_burnDamage; }
    inline unsigned getConfuse() const { return m_confuseDamage; }

private:

    unsigned getAttacker(const unsigned _turnCount){return _turnCount % 2;}
    unsigned getDefender(const unsigned _turnCount){return (1+_turnCount) % 2;}


    int applyWeakRes(std::array<Bench, 2> &_bench,
                     const unsigned &_turnCount);

    int applyBonusDamage(std::array<Bench, 2> &_bench,
                         const unsigned &_turnCount,
                         const unsigned &_defenderIndex,
                         const PTCG::ORDER &_order);


    int m_weaknessMult = 2;
    int m_resistance = - 20;
    unsigned m_poisonDamage = 10;
    unsigned m_burnDamage = 20;
    unsigned m_confuseDamage = 30;


//    BASE + NULL         + WEAKNESS/RES   + NULL
//    BASE + BONUS        + WEAKNESS/RES   + NULL
//    BASE + WEAKNESS/RES + NULL           + NULL
//    BASE + WEAKNESS/RES + BONUS          + NULL
//    BASE + BONUS        + WEAKNESS/RES   + BONUS
//    BASE + BONUS        + NULL           + BONUS
//    BASE + NULL         + NULL           + NULL
};

#endif // DAMAGEHANDLER_H