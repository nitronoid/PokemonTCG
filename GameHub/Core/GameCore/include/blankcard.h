#ifndef BLANKCARD_H
#define BLANKCARD_H

#include "card.h"

class BlankCard : public Card
{
public:
  BlankCard(const BlankCard&) = default;
  BlankCard& operator=(const BlankCard&) = default;
  BlankCard() : Card(~0, "", Ability{}) {}


  virtual bool canPlay(Game&_game) const override;
  virtual Card* clone() override;
  virtual PTCG::CARD cardType() const override;

};

bool BlankCard::canPlay(Game&_game) const { return true; }
Card* BlankCard::clone() { return new BlankCard(*this); }
PTCG::CARD BlankCard::cardType() const{ return PTCG::CARD::BLANK;}

#endif // BLANKCARD_H
