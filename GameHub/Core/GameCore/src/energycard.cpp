#include "energycard.h"

bool EnergyCard::canPlay() const { std::cout<<"yo\n"; return true; }

Card* EnergyCard::clone()
{
  return new EnergyCard(*this);
}

PTCG::TYPE EnergyCard::type() const { return m_type; }

unsigned EnergyCard::amount() const { return m_amount; }

PTCG::CARD EnergyCard::cardType() const { return PTCG::CARD::ENERGY; }
