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
  Attack() = default;
  Attack(const Attack&) = default;
  Attack& operator =(const Attack&) = default;
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

  inline void attack(Game& _game) const { activate(_game); }
  inline bool canAttack(Game& _game) const { return canActivate(_game); }
  inline std::vector<PTCG::TYPE> requirements() const { return m_requirements; }
  inline std::string damageString() const { return m_damageString; }

private:
  std::string m_damageString;
  std::vector<PTCG::TYPE> m_requirements;
};

#endif // ATTACK_H
