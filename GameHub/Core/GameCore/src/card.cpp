#include "card.h"

void Card::activateAbility(Game& _game) const
{
  m_ability.use(_game);
}
