#ifndef DAMAGEHANDLER_H
#define DAMAGEHANDLER_H
#include "bench.h"

class DamageHandler
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  DamageHandler()=default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment copy operator
  //----------------------------------------------------------------------------------------------------------------------
  DamageHandler& operator =(const DamageHandler &_original) = delete;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor for DamageHandler
  //----------------------------------------------------------------------------------------------------------------------
  ~DamageHandler() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief removing damage taken by a healing a pokemon
  /// @param [in] _slot pokemon on a bench slot, to be healed
  /// @param [in] _value healing amount
  /// @return whether the healing failed
  //----------------------------------------------------------------------------------------------------------------------
  bool heal(BoardSlot* _slot, const int &_value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dealing damage to a pokemon, factor in weakness, bonus damages for active, factoring only base for benched
  /// @param [in] _attacker bench on the attacking pokemon's side
  /// @param [in] _defender bench on the defending pokemon's side
  /// @param [in] _defenderIndex index of the bench for the defending pokemon
  /// @param [in] _damage base damage of the attack
  /// @param [in] _applyWeak whether the damage needs to apply weakness and resistance
  //----------------------------------------------------------------------------------------------------------------------
  void generalDamage(
      Bench *_attacker,
      Bench *_defender,
      const size_t &_defenderIndex,
      const int &_damage,
      const bool &_applyWeak = true
      );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dealing damage, factor only base damage, simulates "Put x Damage Counters onto xxxx Pokemon from special conditions, attacks effects."
  /// @param [in] _defender the slot for the defending pokemon
  /// @param [in] _damage base damage of the attack/effect
  //----------------------------------------------------------------------------------------------------------------------
  void rawDamage(BoardSlot* _defender, const int &_damage);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Poison damage
  //----------------------------------------------------------------------------------------------------------------------
  void increasePoison(const int _damage);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Burn damage
  //----------------------------------------------------------------------------------------------------------------------
  void increaseBurn(const int _damage);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief increases poison damage
  /// @param [in] _damage how much to increase the Confusion damage
  //----------------------------------------------------------------------------------------------------------------------
  void increaseConfuse(const int _damage);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accessing game poison damage
  /// @return current poison damage per turn
  //----------------------------------------------------------------------------------------------------------------------
  int getPoison() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accessing game burn damage
  /// @return current burn damage per turn
  //----------------------------------------------------------------------------------------------------------------------
  int getBurn() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accessing game confusion damage
  /// @return current confusion damage per tail on coin flip when attacking
  //----------------------------------------------------------------------------------------------------------------------
  int getConfuse() const;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief applying and determining weakness or resisitance within damage calculation
  /// @param [in] _defender slot of the defending pokemon
  /// @param [in] _attacker slot of the attacking pokemon
  /// @return damage reduction when resistant, damage multiplies when weak against attack
  //----------------------------------------------------------------------------------------------------------------------
  int applyWeakRes(BoardSlot* _defender, BoardSlot* _attacker);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief adding the net bonus damage for damage calculation
  /// @param [in] _defender slot of the defending pokemon
  /// @param [in] _attacker slot of the attacking pokemon
  /// @param [in] _order whether you are calculating net bonus before/after weakness/resistance application
  /// @return net bonus damage before/after weakness/resistance calculation
  //----------------------------------------------------------------------------------------------------------------------
  int applyBonusDamage(Status *_defender, Status *_attacker, const PTCG::ORDER &_order);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief weakness multiplier
  //----------------------------------------------------------------------------------------------------------------------
  int m_weaknessMult = 2;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief resistance damage reduction
  //----------------------------------------------------------------------------------------------------------------------
  int m_resistance = - 20;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief base poison damage
  //----------------------------------------------------------------------------------------------------------------------
  int m_poisonDamage = 10;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief base burn damage
  //----------------------------------------------------------------------------------------------------------------------
  int m_burnDamage = 20;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief base confusion damage
  //----------------------------------------------------------------------------------------------------------------------
  int m_confuseDamage = 30;
};

#endif // DAMAGEHANDLER_H
