#include "card/blankcard.h"


bool BlankCard::canPlay(Game&) const
{
  return false;
}


void BlankCard::playCard(Game&, size_t)
{
  // nothing
}

Card* BlankCard::clone()
{
  return new BlankCard(*this);
}

PTCG::CARD BlankCard::cardType() const
{
  return PTCG::CARD::BLANK;
}
