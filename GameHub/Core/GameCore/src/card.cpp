#include "card.h"

Card::~Card() = default;

void Card::activateAbility(Game& _game) const
{
  m_ability.use(_game);
}
