#include "effect/attack.h"

Attack::~Attack() = default;

void Attack::attack(Game& _game) const
{
  activate(_game);
}

bool Attack::canAttack(Game& _game) const
{
  return canActivate(_game);
}

std::vector<PTCG::TYPE> Attack::requirements() const
{
  return m_requirements;
}

std::string Attack::damageString() const
{
  return m_damageString;
}
