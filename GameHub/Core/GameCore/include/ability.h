#ifndef ABILITY_H
#define ABILITY_H

#include <functional>
#include "pokemonenums.h"

class Game;
using AbilityFunc = std::function<void(Game*)>;
using CanPlayFunc = std::function<bool(Game*const)>;

class Ability
{
public:
  Ability() = default;
  Ability(const Ability&) = default;
  Ability& operator =(const Ability&) = default;
  Ability(
      const AbilityFunc _ability,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      const std::function<bool(Game*const)> _canUse
      ) :
    m_ability(_ability),
    m_trigger(_trigger),
    m_duration(_duration),
    m_canUse(_canUse)
  {}

  inline void use(Game& _game) const { m_ability(&_game); }
  inline PTCG::TRIGGER getTrigger() const { return  m_trigger; }
  inline PTCG::DURATION getDuration() const { return m_duration; }
  inline bool canUse(Game&_game) const { return m_canUse(&_game);}

private:
  AbilityFunc m_ability;
  PTCG::TRIGGER m_trigger = PTCG::TRIGGER::NONE;
  PTCG::DURATION m_duration = PTCG::DURATION::PERMANENT;

  std::function<bool(Game*const)> m_canUse = [](auto){return true;};
};

#endif // ABILITY_H
