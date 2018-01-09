#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"

class Ability : public Effect
{
public:
  Ability() = default;
  Ability(const Ability&) = default;
  Ability& operator =(const Ability&) = default;
  Ability(
      const EffectFunc _ability,
      const std::string &_name,
      const PTCG::TRIGGER _trigger,
      const PTCG::DURATION _duration,
      const std::function<bool(Game*const)> _canUse = [](auto){return true;}
      ) :
    Effect (_ability, _name, _trigger, _duration, _canUse)
  {}

  inline void use(Game& _game) const { activate(_game); }
  inline bool canUse(Game&_game) const { return canActivate(_game);}

};

#endif // ABILITY_H
