#ifndef ATTACK_H
#define ATTACK_H

#include <functional>
#include <string>
#include <pokemonenums.h>

class Game;
using AttackFunc = std::function<void(Game*)>;

class Attack
{
public:
  Attack() = default;
  Attack(const Attack&) = default;
  Attack& operator =(const Attack&) = default;
  Attack(const AttackFunc _attack, const std::string &_name, std::vector<PTCG::TYPE> &&_requirements) :
    m_name(_name),
    m_attack(_attack),
    m_requirements(_requirements)
  {}

  inline void attack(Game& _game) const { m_attack(&_game); }
private:

  std::string m_name;
  AttackFunc m_attack;
  std::vector<PTCG::TYPE> m_requirements;
};

#endif // ATTACK_H
