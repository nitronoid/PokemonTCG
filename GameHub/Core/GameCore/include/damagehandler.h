#ifndef DAMAGEHANDLER_H
#define DAMAGEHANDLER_H
#include "bench.h"

class DamageHandler
{
public:

  DamageHandler()=default;
  DamageHandler& operator =(const DamageHandler &_original) = delete;

  bool heal(BoardSlot* _slot, const int &_value);

  //factor in weakness, bonus damages for active, factoring only bonus for benched
  void generalDamage(
      Bench *_attacker,
      Bench *_defender,
      const size_t &_defenderIndex,
      const int &_damage,
      const bool &_applyWeak = true
      );

  //factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon from special conditions, attacks."
  void rawDamage(BoardSlot* _defender, const int &_damage);


  void increasePoison(const int _damage);
  void increaseBurn(const int _damage);
  void increaseConfuse(const int _damage);
  inline int getPoison() const { return m_poisonDamage; }
  inline int getBurn() const { return m_burnDamage; }
  inline int getConfuse() const { return m_confuseDamage; }

private:
  int applyWeakRes(BoardSlot* _defender, BoardSlot* _attacker);
  int applyBonusDamage(Status *_defender, Status *_attacker, const PTCG::ORDER &_order);


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

#endif // DAMAGEHANDLER_H
