#ifndef TRAINERCARD_H
#define TRAINERCARD_H

#include "card.h"

class TrainerCard : public Card
{
public:
  TrainerCard(const TrainerCard&) = default;
  TrainerCard(const unsigned _id, const std::string &_name, const Ability _ability, const PTCG::TRAINER _type) :
    Card(_id, _name, _ability),
    m_type(_type)
  {}

  virtual Card* clone() override
  {
    return new TrainerCard(*this);
  }

private:
  PTCG::TRAINER m_type;

};

#endif // TRAINERCARD_H
