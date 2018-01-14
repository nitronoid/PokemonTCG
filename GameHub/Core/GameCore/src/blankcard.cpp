#include "blankcard.h"


bool BlankCard::canPlay(Game&) const { return true; }

Card* BlankCard::clone() { return new BlankCard(*this); }

PTCG::CARD BlankCard::cardType() const{ return PTCG::CARD::BLANK;}
