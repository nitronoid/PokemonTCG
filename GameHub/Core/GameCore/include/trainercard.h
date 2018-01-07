#ifndef TRAINERCARD_H
#define TRAINERCARD_H

#include "card.h"

class TrainerCard : public Card
{
public:
  TrainerCard(const TrainerCard&) = default;
  TrainerCard(
      const unsigned _id,
      const std::string &_name,
      const Ability &_ability,
      const PTCG::CARD _type
      ) :
    Card(_id, _name, _ability),
    m_type(_type)
  {}

  virtual Card* clone() override;
  virtual bool canPlay(Game &_game) const override;
  virtual PTCG::CARD cardType() const override;
private:
  PTCG::CARD m_type;

};

#endif // TRAINERCARD_H
