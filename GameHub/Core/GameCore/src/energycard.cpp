#include "energycard.h"
#include "game.h"

bool EnergyCard::canPlay(Game &) const
{
  return true;
}

void EnergyCard::playCard(Game&_game, const size_t _index)
{
   _game.playEnergy(static_cast<EnergyCard*>(this), _index);
}

Card* EnergyCard::clone()
{
  return new EnergyCard(*this);
}

PTCG::TYPE EnergyCard::type() const
{
  return m_type;
}

unsigned EnergyCard::amount() const
{
  return m_amount;
}

PTCG::CARD EnergyCard::cardType() const
{
  return PTCG::CARD::ENERGY;
}
