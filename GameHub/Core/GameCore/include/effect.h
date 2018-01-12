#ifndef EFFECT_H
#define EFFECT_H

#include <functional>
#include "pokemonenums.h"

class Game;
using EffectFunc = std::function<void(Game*)>;
using CanPlayFunc = std::function<bool(Game*const)>;

class Effect
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor for Effect
  //----------------------------------------------------------------------------------------------------------------------
  Effect() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor for Effect
  //----------------------------------------------------------------------------------------------------------------------
  Effect(const Effect&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy assignment op for Effect
  //----------------------------------------------------------------------------------------------------------------------
  Effect& operator =(const Effect&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for Effect
  //----------------------------------------------------------------------------------------------------------------------
  Effect(
      const EffectFunc _ability,
      const std::string &_name,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      const std::function<bool(Game*const)> _canUse = [](auto){return true;}
  ) :
    m_name(_name),
    m_ability(_ability),
    m_trigger(_trigger),
    m_duration(_duration),
    m_canUse(_canUse)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default virtual dtor for Effect
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Effect();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the trigger of the effect
  /// @return this effects trigger
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TRIGGER getTrigger() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the duration of the effect
  /// @return this effects duration
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::DURATION getDuration() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the name of the effect
  /// @return this effects name
  //----------------------------------------------------------------------------------------------------------------------
  std::string name() const;

protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for activating the effect
  /// @param [in] _game reference game instance
  //----------------------------------------------------------------------------------------------------------------------
  void activate(Game& _game) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for validating the effect activation
  /// @param [in] _game reference game instance
  /// @return whether this effect can be activated
  //----------------------------------------------------------------------------------------------------------------------
  bool canActivate(Game&_game) const;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the name of the effect
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_name;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the effect function of the effect
  //----------------------------------------------------------------------------------------------------------------------
  EffectFunc m_ability;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the effect trigger
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TRIGGER m_trigger = PTCG::TRIGGER::NONE;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the duration of the effect
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::DURATION m_duration = PTCG::DURATION::PERMANENT;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief usage validation function stored as variable
  //----------------------------------------------------------------------------------------------------------------------
  std::function<bool(Game*const)> m_canUse = [](auto){return true;};
};

#endif // EFFECT_H
