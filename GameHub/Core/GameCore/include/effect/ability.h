#ifndef ABILITY_H
#define ABILITY_H

#include "effect/effect.h"

class Ability : public Effect
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Ability() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  Ability(const Ability&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  Ability& operator=(const Ability&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief specific assignment ctor for constructing an Ability
  /// @param [in] _ability effect function to be executed/used
  /// @param [in] _name name of the attack, effect or ability
  /// @param [in] _trigger when the effect is triggered
  /// @param [in] _duration how does the effect wear off/number of use
  /// @param [in] _canUse function to check if effect can be used
  //----------------------------------------------------------------------------------------------------------------------
  Ability(
      const EffectFunc _ability,
      const std::string &_name,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      const std::function<bool(Game*const)> _canUse = [](auto){return true;}
  ) :
    Effect (_ability, _name, _trigger, _duration, _canUse)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default virtual dtor for Ability
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Ability();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for activing an ability, requires a game for function calls.
  /// @param [in] _game current game state to affect.
  //----------------------------------------------------------------------------------------------------------------------
  void use(Game& _game) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method loaded from cards to check if the effects can be activated before use()
  /// @param [in] _game game state to check before using ability.
  /// @return whether the ability can be used or not
  //----------------------------------------------------------------------------------------------------------------------
  bool canUse(Game&_game) const;

};

#endif // ABILITY_H
