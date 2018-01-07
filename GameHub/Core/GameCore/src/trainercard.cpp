#include "trainercard.h"

Card* TrainerCard::clone()
{
  return new TrainerCard(*this);
}

bool TrainerCard::canPlay(Game &_game) const { return m_ability.canUse(_game); }

PTCG::CARD TrainerCard::cardType() const { return m_type; }
