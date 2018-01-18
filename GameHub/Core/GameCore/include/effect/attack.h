#ifndef ATTACK_H
#define ATTACK_H

#include <functional>
#include <string>
#include <vector>
#include <pokemonenums.h>
#include "effect/ability.h"

class Attack : public Effect
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Attack() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  Attack(const Attack&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  Attack& operator =(const Attack&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief specific assignment ctor for constructing an Attack
  /// @param [in] _attack function to be executed/used, loaded from cards
  /// @param [in] _name name of the attack, effect or ability
  /// @param [in] _dmgString base damage to display
  /// @param [in] _trigger when the effect is triggered
  /// @param [in] _duration how does the effect wear off/number of use
  /// @param [in] _requirement a vector containing the required energies for using this attack
  /// @param [in] _canUse function to check if attack can be used
  //----------------------------------------------------------------------------------------------------------------------
  Attack(
      const EffectFunc _attack,
      const std::string &_name,
      const std::string &_dmgString,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      std::vector<PTCG::TYPE> &&_requirements,
      const std::function<bool(Game*const)> _canUse = [](auto){return true;}
  ) :
    Effect (_attack, _name, _trigger, _duration, _canUse),
    m_damageString(_dmgString),
    m_requirements(_requirements)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default virtual dtor for Attack
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Attack();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to call the attack effect methods
  /// @param [in] _game current game state to affect
  //----------------------------------------------------------------------------------------------------------------------
  void attack(Game& _game) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to check for valid attack condition
  /// @param [in] _game current game state to check
  /// @return whether the attack can be used or not
  //----------------------------------------------------------------------------------------------------------------------
  bool canAttack(Game& _game) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to return energy requirements of the attacks
  /// @return a list of energy cards needed to use the attack
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<PTCG::TYPE> requirements() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to return base damage text
  /// @return the base damage string of an attack
  //----------------------------------------------------------------------------------------------------------------------
  std::string damageString() const;

private:
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief base damage for the attack
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_damageString;
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief energy requirements for the attack
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<PTCG::TYPE> m_requirements;
};

#endif // ATTACK_H
