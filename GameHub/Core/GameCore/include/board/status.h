#ifndef STATUS_H
#define STATUS_H

#include "pokemonenums.h"
#include <unordered_set>
#include <array>
#include <vector>

struct Status
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Status() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~Status() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get bonus damage
  /// @param [in] apllication order
  /// @return bonus damage value
  //----------------------------------------------------------------------------------------------------------------------
  int getBonus(const PTCG::ORDER _order) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get resistance (damage reduction)
  /// @param [in] application order
  /// @return damage reduction value
  //----------------------------------------------------------------------------------------------------------------------
  int getReduction(const PTCG::ORDER _order) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get protection value
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  bool isProtected() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get retreat switch value
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  bool canRetreat() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for resetting the Status
  //----------------------------------------------------------------------------------------------------------------------
  void resetAll();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset bonuses and switches
  //----------------------------------------------------------------------------------------------------------------------
  void resetForNextTurn();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset damage bonuses
  //----------------------------------------------------------------------------------------------------------------------
  void resetAllDamageBonuses();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset a single damage bonus
  /// @param [in] application order
  //----------------------------------------------------------------------------------------------------------------------
  void resetDamageBonus(const PTCG::ORDER &_order);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset defense bonuses
  //----------------------------------------------------------------------------------------------------------------------
  void resetAllDefenseBonuses();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reset single defense bonus
  /// @param [in] application order
  //----------------------------------------------------------------------------------------------------------------------
  void resetDefenseBonus(const PTCG::ORDER &_order);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief add bonus damage
  /// @param [in] application order
  /// @param [in] bonus value
  //----------------------------------------------------------------------------------------------------------------------
  void addBonusDamage(const PTCG::ORDER &_order, const unsigned &_value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief add bonus resistance (defense)
  /// @param [in] application order
  /// @param [in] bonus value
  //----------------------------------------------------------------------------------------------------------------------
  void addBonusDefense(const PTCG::ORDER &_order, const unsigned &_value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief add condition
  /// @param [in] condition type
  //----------------------------------------------------------------------------------------------------------------------
  void addCondition(const PTCG::CONDITION _condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief remove condition
  /// @param [in] condition type
  //----------------------------------------------------------------------------------------------------------------------
  void removeCondition(const PTCG::CONDITION _condition);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief remove all conditions
  //----------------------------------------------------------------------------------------------------------------------
  void removeAllConditions();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check if condition is applied
  /// @param [in] condition type
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  bool hasCondition(const PTCG::CONDITION _condition) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get all conditions
  /// @return vector of condition enums
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<PTCG::CONDITION> conditions() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle protection switch
  /// @param [in] new value
  //----------------------------------------------------------------------------------------------------------------------
  void setProtected(const bool &_val);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief toggle retreat switch
  /// @param [in] new value
  //----------------------------------------------------------------------------------------------------------------------
  void setCanRetreat(const bool &_val);
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief applied conditions
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_set<PTCG::CONDITION> m_conditions;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bonus damages
  //----------------------------------------------------------------------------------------------------------------------
  std::array<int, 2> m_bonusDamage = {{0, 0}};
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief bonus resistances
  //----------------------------------------------------------------------------------------------------------------------
  std::array<int, 2> m_damageReduction = {{0, 0}};
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief protection switch
  //----------------------------------------------------------------------------------------------------------------------
  bool m_protected = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief retreat switch
  //----------------------------------------------------------------------------------------------------------------------
  bool m_canRetreat = true;
};


#endif // STATUS_H