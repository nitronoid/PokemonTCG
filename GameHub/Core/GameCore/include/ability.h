#ifndef ABILITY_H
#define ABILITY_H

#include <functional>
#include "pokemonenums.h"

class Game;
using AbilityFunc = std::function<void(Game*)>;

class Ability
{
public:
  Ability() = default;
  Ability(const Ability&) = default;
  Ability& operator =(const Ability&) = default;
  Ability(const AbilityFunc _ability, const PTCG::TRIGGER _trigger, const PTCG::DURATION _duration) :
    m_ability(_ability),
    m_trigger(_trigger),
    m_duration(_duration)
  {}

  inline void use(Game& _game) const { m_ability(&_game); }
  inline PTCG::TRIGGER getTrigger() const { return  m_trigger; }
  inline PTCG::DURATION getDuration() const { return m_duration; }

private:
  AbilityFunc m_ability;
  PTCG::TRIGGER m_trigger = PTCG::TRIGGER::NONE;
  PTCG::DURATION m_duration = PTCG::DURATION::PERMANENT;
};

#endif // ABILITY_H
