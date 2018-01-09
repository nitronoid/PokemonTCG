#ifndef CARD_H
#define CARD_H

#include "ability.h"
#include <string>
#include <iostream>

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

  virtual ~Card();

  virtual bool canPlay(Game&_game) const = 0;
  virtual Card* clone() = 0;
  virtual PTCG::CARD cardType() const = 0;
  void activateAbility(Game &_game) const;
  inline std::string getName() const{return m_name;}
  inline unsigned getID()const{return m_id;}

protected:
  Ability m_ability;
private:
  std::string m_name;
  unsigned m_id;
};

#endif // CARD_H
