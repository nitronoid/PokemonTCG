#include "effect/ability.h"

Ability::~Ability() = default;

void Ability::use(Game& _game) const
{
  activate(_game);
}

bool Ability::canUse(Game&_game) const
{
  return canActivate(_game);
}
