#include "damagehandler.h"

bool DamageHandler::heal(BoardSlot *_slot, const int &_value)
{
  if(_slot->getDamage()>0)
  {
    _slot->removeDamage(_value);
    return true;
  }
  std::cout<<"Full Health, this does nothing"<<'\n';
  return false;

}

void DamageHandler::generalDamage(Bench *_attacker,
    Bench *_defender,
    const size_t &_defenderIndex,
    const int &_damage,
    const bool &_applyWeak)
{
  int totalDamage;
  auto attackerSlot = _defender->slotAt(0);
  auto defenderSlot = _defender->slotAt(_defenderIndex);
  //If this is an active pokemon and applies weakness/res:
  auto attackerStatus = _attacker->activeStatus();
  auto defenderStatus = _defender->activeStatus();
  if(!_defenderIndex && _applyWeak)
  {
    int weakRes = applyWeakRes(defenderSlot, attackerSlot);
    //if it says -20, it's resistance and 2 for weakness multiplier
    if(weakRes<=0)
    {
      totalDamage =
          _damage + applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::BEFORE) +
          weakRes + applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::AFTER);
      defenderSlot->takeDamage(std::max(0,totalDamage));
    }
    else
    {
      totalDamage =
          (_damage + applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::BEFORE)) *
          weakRes + applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::AFTER);
      defenderSlot->takeDamage(std::max(0,totalDamage));
    }
  }
  else if(!_defenderIndex && _applyWeak)
  {
    totalDamage =
        _damage + applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::BEFORE) +
        applyBonusDamage(defenderStatus, attackerStatus, PTCG::ORDER::AFTER);
    defenderSlot->takeDamage(std::max(0,totalDamage));
  }
  else //if target is bench
  {
    totalDamage = _damage;
    defenderSlot->takeDamage(std::max(0,totalDamage));
  }


}

void DamageHandler::rawDamage(BoardSlot* _defender, const int &_damage)
{
  std::cout<<"Taking "<<_damage<<" damage from effects."<<'\n';
  _defender->takeDamage(_damage);
}

int DamageHandler::applyWeakRes(BoardSlot* _defender, BoardSlot* _attacker)
{
  if(_attacker->active()->type() == _defender->active()->weakness())
  {
    return m_weaknessMult;
  }
  else if (_attacker->active()->type() == _defender->active()->resistance())
  {
    return m_resistance;
  }
  return 0;
}


int DamageHandler::applyBonusDamage(Status* _defender, Status* _attacker, const PTCG::ORDER &_order)
{
  return _attacker->getBonus(_order) - _defender->getReduction(_order);
}


void DamageHandler::increaseBurn(const int _damage)
{
  m_burnDamage+=_damage;
}

void DamageHandler::increaseConfuse(const int _damage)
{
  m_confuseDamage+=_damage;
}

void DamageHandler::increasePoison(const int _damage)
{
  m_poisonDamage+=_damage;
}

