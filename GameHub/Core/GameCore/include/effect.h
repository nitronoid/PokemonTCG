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
  Effect() = default;
  Effect(const Effect&) = default;
  Effect& operator =(const Effect&) = default;
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
  ~Effect() = default;

  inline PTCG::TRIGGER getTrigger() const { return  m_trigger; }
  inline PTCG::DURATION getDuration() const { return m_duration; }
  inline std::string name() const { return m_name; }

protected:
  inline void activate(Game& _game) const { m_ability(&_game); }
  inline bool canActivate(Game&_game) const { return m_canUse(&_game);}

private:
  std::string m_name;
  EffectFunc m_ability;
  PTCG::TRIGGER m_trigger = PTCG::TRIGGER::NONE;
  PTCG::DURATION m_duration = PTCG::DURATION::PERMANENT;

  std::function<bool(Game*const)> m_canUse = [](auto){return true;};
};

#endif // EFFECT_H
