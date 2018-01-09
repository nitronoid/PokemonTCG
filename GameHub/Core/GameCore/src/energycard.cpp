#include "energycard.h"

bool EnergyCard::canPlay(Game &) const { return true; }

Card* EnergyCard::clone()
{
  return new EnergyCard(*this);
}

PTCG::TYPE EnergyCard::type() const { return m_type; }

unsigned EnergyCard::amount() const { return m_amount; }

PTCG::CARD EnergyCard::cardType() const { return PTCG::CARD::ENERGY; }
