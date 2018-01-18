#include "board/status.h"

int  Status::getBonus(const PTCG::ORDER _order) const
{
  return m_bonusDamage[static_cast<size_t>(_order)];
}

int  Status::getReduction(const PTCG::ORDER _order) const
{
  return m_damageReduction[static_cast<size_t>(_order)];
}

bool Status::isProtected() const
{
  return m_protected;
}

bool Status::canRetreat() const
{
  return m_canRetreat;
}

void Status::resetAll()
{
  resetForNextTurn();
  removeAllConditions();
}

void Status::resetForNextTurn()
{
  resetAllDamageBonuses();
  resetAllDefenseBonuses();
  m_protected = false;
  m_canRetreat = true;
}

void Status::resetAllDamageBonuses()
{
  resetDamageBonus(PTCG::ORDER::AFTER);
  resetDamageBonus(PTCG::ORDER::BEFORE);
}

void Status::resetAllDefenseBonuses()
{
  resetDefenseBonus(PTCG::ORDER::AFTER);
  resetDefenseBonus(PTCG::ORDER::BEFORE);
}

void Status::resetDamageBonus(const PTCG::ORDER &_order)
{
  m_bonusDamage[static_cast<size_t>(_order)] = 0;
}

void Status::resetDefenseBonus(const PTCG::ORDER &_order)
{
  m_damageReduction[static_cast<size_t>(_order)] = 0;
}

void Status::addBonusDamage(const PTCG::ORDER &_order, const unsigned &_value)
{
  m_bonusDamage[static_cast<size_t>(_order)] += _value;
}

void Status::addBonusDefense(const PTCG::ORDER &_order, const unsigned &_value)
{
  m_damageReduction[static_cast<size_t>(_order)] += _value;
}

void Status::addCondition(const PTCG::CONDITION _condition)
{
  using cnd = PTCG::CONDITION;
  if(_condition == cnd::ASLEEP    ||
     _condition == cnd::CONFUSED  ||
     _condition == cnd::PARALYZED
     )
  {
    m_conditions.erase(cnd::ASLEEP);
    m_conditions.erase(cnd::CONFUSED);
    m_conditions.erase(cnd::PARALYZED);
  }
  m_conditions.insert(_condition);
}

void Status::removeCondition(const PTCG::CONDITION _condition)
{
  m_conditions.erase(_condition);
}

void Status::removeAllConditions()
{
  m_conditions.clear();
}

bool Status::hasCondition(const PTCG::CONDITION _condition) const
{
  return m_conditions.count(_condition);
}

std::vector<PTCG::CONDITION> Status::conditions() const
{
  std::vector<PTCG::CONDITION> cond(m_conditions.begin(), m_conditions.end());
  return cond;
}

void Status::setProtected(const bool &_val)
{
  m_protected=_val;
}

void Status::setCanRetreat(const bool &_val)
{
  m_canRetreat=_val;
}
