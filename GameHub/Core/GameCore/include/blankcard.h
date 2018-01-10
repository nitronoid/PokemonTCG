#ifndef BLANKCARD_H
#define BLANKCARD_H

#include "card.h"

class BlankCard : public Card
{
public:
  BlankCard(const BlankCard&) = default;
  BlankCard& operator=(const BlankCard&) = default;
  BlankCard() : Card(~0, "", Ability{}) {}


  virtual bool canPlay(Game&) const override;
  virtual Card* clone() override;
  virtual PTCG::CARD cardType() const override;

};


#endif // BLANKCARD_H
