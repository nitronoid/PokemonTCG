#ifndef CARD_H
#define CARD_H

#include "ability.h"
#include <string>

using AttackFunc = AbilityFunc;

class Card
{
protected:
  Card(const Card&) = default;
  Card(const int _id, const std::string &_name, const Ability & _ability) :
    m_ability(_ability),
    m_name(_name),
    m_id(_id)
  {}

public:
  void activateAbility(const Game &_game) const;

private:
  const Ability m_ability;
  const std::string m_name;
  const int m_id;
};

#endif // CARD_H
