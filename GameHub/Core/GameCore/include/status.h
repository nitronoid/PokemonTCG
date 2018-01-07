#ifndef STATUS_H
#define STATUS_H

#include "pokemonenums.h"
#include <unordered_set>
#include <array>
#include <vector>

struct Status
{
public:
  Status() = default;
  inline int  getBonus(const PTCG::ORDER _order)     const { return m_bonusDamage[static_cast<size_t>(_order)]; }
  inline int  getReduction(const PTCG::ORDER _order) const { return m_damageReduction[static_cast<size_t>(_order)]; }
  inline bool isProtected()        const { return m_protected; }
  void resetAll()
  {
    resetDamageEffects();
    removeAllConditions();
  }

  void resetDamageEffects()
  {
    resetAllDamageBonuses();
    resetAllDefenseBonuses();
    m_protected = false;
  }

  void resetAllDamageBonuses()
  {
    resetDamageBonus(PTCG::ORDER::AFTER);
    resetDamageBonus(PTCG::ORDER::BEFORE);
  }

  void resetDamageBonus(const PTCG::ORDER &_order);
  void resetAllDefenseBonuses()
  {
    resetDefenseBonus(PTCG::ORDER::AFTER);
    resetDefenseBonus(PTCG::ORDER::BEFORE);
  }

  void resetDefenseBonus(const PTCG::ORDER &_order);
  void addBonusDamage(const PTCG::ORDER &_order, const unsigned &_value);
  void addBonusDefense(const PTCG::ORDER &_order, const unsigned &_value);

  void addCondition(const PTCG::CONDITION _condition);
  void removeCondition(const PTCG::CONDITION _condition);
  void removeAllConditions();
  std::vector<PTCG::CONDITION> conditions() const;
  void setProtected(const bool &_val);
private:
  std::unordered_set<PTCG::CONDITION> m_conditions;
  std::array<int, 2> m_bonusDamage     = {{0, 0}};
  std::array<int, 2> m_damageReduction = {{0, 0}};
  bool m_protected = false;
};


#endif // STATUS_H
