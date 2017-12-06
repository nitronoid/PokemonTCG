#ifndef CARD_H
#define CARD_H

#include "ability.h"
#include <string>

class Card
{
public:
  Card(const Card&) = default;
  Card& operator=(const Card&) = default;
  Card(const unsigned _id, const std::string &_name, const Ability & _ability) :
    m_ability(_ability),
    m_name(_name),
    m_id(_id)
  {}

  virtual ~Card(){}

  virtual bool canPlay() = 0;
  virtual Card* clone() = 0;
  void activateAbility(Game &_game) const;

private:
  Ability m_ability;
  std::string m_name;
  unsigned m_id;
};

#endif // CARD_H
