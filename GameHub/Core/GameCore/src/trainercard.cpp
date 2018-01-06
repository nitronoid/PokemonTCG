#include "trainercard.h"

Card* TrainerCard::clone()
{
  return new TrainerCard(*this);
}

bool TrainerCard::canPlay() const { return m_canPlay(); }

PTCG::CARD TrainerCard::cardType() const { return m_type; }
