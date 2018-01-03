#ifndef TRAINERCARD_H
#define TRAINERCARD_H

#include "card.h"

class TrainerCard : public Card
{
public:
  TrainerCard(const TrainerCard&) = default;
  TrainerCard(const unsigned _id, const std::string &_name, const Ability &_ability, const PTCG::CARD _type) :
    Card(_id, _name, _ability),
    m_type(_type)
  {}

  virtual Card* clone() override
  {
    return new TrainerCard(*this);
  }
  inline virtual bool canPlay() override { return m_canPlay(); }
  virtual PTCG::CARD cardType() const override { return m_type; }
private:
  PTCG::CARD m_type;
  std::function<bool()> m_canPlay;

};

#endif // TRAINERCARD_H
