#ifndef ATTACK_H
#define ATTACK_H

#include <functional>
#include <string>
#include <vector>
#include <pokemonenums.h>
#include "ability.h"

class Attack : public Effect
{
public:
  /// @brief default ctor
  Attack() = default;
  /// @brief default cooy ctor
  Attack(const Attack&) = default;
  /// @brief assignment operator for copy assignment
  Attack& operator =(const Attack&) = default;
  /// @brief specific assignment ctor for constructing an Ability
  /// @param [in] _attack function to be executed/used, loaded from cards
  /// @param [in] _name name of the attack, effect or ability
  /// @param [in] _dmgString damage display
  /// @param [in] _trigger when the effect is triggered
  /// @param [in] _duration how does the effect wear off/number of use
  /// @param [in] _requirement containers of energy requirements for the attacks
  /// @param [in] _canUse function to check if effect can be used
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
  /// @brief method to call the attack effect methods
  /// @param [in] _game current game state to affect
  inline void attack(Game& _game) const { activate(_game); }
  /// @brief method to check for valid attack condition
  /// @param [in] _game current game state to check
  inline bool canAttack(Game& _game) const { return canActivate(_game); }
  /// @brief method to return energy requirements of the attacks
  inline std::vector<PTCG::TYPE> requirements() const { return m_requirements; }
  /// @brief method to return damage text
  inline std::string damageString() const { return m_damageString; }

private:
  ///@brief base damage for the attack
  std::string m_damageString;
  ///@brief energy requirements for the attack
  std::vector<PTCG::TYPE> m_requirements;
};

#endif // ATTACK_H
