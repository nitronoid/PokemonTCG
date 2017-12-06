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
  Ability(const AbilityFunc _ability, const PTCG::PHASE _phase, const PTCG::DURATION _duration) :
    m_ability(_ability),
    m_ablityPhase(_phase),
    m_abilityDuration(_duration)
  {}

  inline void use(Game& _game) const { m_ability(&_game); }
private:
  AbilityFunc m_ability;
  PTCG::PHASE m_ablityPhase = PTCG::PHASE::NONE;
  PTCG::DURATION m_abilityDuration = PTCG::DURATION::PERMANENT;
};

#endif // ABILITY_H
