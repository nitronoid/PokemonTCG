#include "card.h"

void Card::activateAbility(const Game& _game) const
{
  m_ability.use(_game);
}
