#include "card/card.h"

Card::~Card() = default;

void Card::activateAbility(Game& _game) const
{
  m_ability.use(_game);
}

std::string Card::getName() const
{
  return m_name;
}

unsigned Card::getID() const
{
  return m_id;
}
