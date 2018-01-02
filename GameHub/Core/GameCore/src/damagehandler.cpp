#include "damagehandler.h"

bool DamageHandler::heal(
    Bench &_bench,
    const unsigned &_benchIndex,
    const unsigned &_value)
{
  if(_bench.slotAt(_benchIndex)->getDamage()>0)
  {

      _bench.slotAt(_benchIndex)->removeDamage(_value);
      return true;
  }
  std::cout<<"Full Health, this does nothing"<<'\n';
  return false;

}

void DamageHandler::generalDamage(
    Bench &_bench,
    BoardSlot &_attacker,
    const unsigned &_defenderIndex,
    const unsigned &_damage)
{
    unsigned totalDamage;
    //If this is an active pokemon:
    if(_defenderIndex == 0)
    {
        int weakRes = applyWeakRes(_bench.view().at(0),_attacker);
        //if it says -20, it's resistance and 2 for weakness multiplier
        if(weakRes<=0)
        {
            totalDamage =
                _damage                               +
                applyBonusDamage(_bench.view().at(0),
                                 _attacker,
                                 PTCG::ORDER::BEFORE) +
                weakRes                               +
                applyBonusDamage(_bench.view().at(0),
                                 _attacker,
                                 PTCG::ORDER::AFTER);
                _bench.slotAt(_defenderIndex)->takeDamage(totalDamage);
        }
        else
        {
            totalDamage =
                (
                _damage                                +
                applyBonusDamage(_bench.view().at(0),
                                 _attacker,
                                 PTCG::ORDER::BEFORE)) *
                weakRes                                +
                applyBonusDamage(_bench.view().at(0),
                                 _attacker,
                                 PTCG::ORDER::AFTER);

                _bench.slotAt(_defenderIndex)->takeDamage(totalDamage);
        }
    }
    else //if target is bench
    {
      totalDamage = _damage                               +
          applyBonusDamage(_bench.view().at(_defenderIndex),
                           _attacker,
                           PTCG::ORDER::BEFORE)           +
          applyBonusDamage(_bench.view().at(_defenderIndex),
                           _attacker,
                           PTCG::ORDER::AFTER);
          _bench.slotAt(_defenderIndex)->takeDamage(totalDamage);
    }


}

void DamageHandler::rawDamage(
    Bench &_bench,
    const unsigned &_defenderIndex,
    const unsigned &_damage)
{
  std::cout<<"Taking "<<_damage<<" damage from effects."<<'\n';
   _bench.slotAt(_defenderIndex)->takeDamage(_damage);
}

int DamageHandler::applyWeakRes(BoardSlot &_defender, BoardSlot &_attacker)
{
  if(_attacker.active()->type() == _defender.active()->weakness())
  {
    return m_weaknessMult;
  }
  else if (_attacker.active()->type() == _defender.active()->resistance())
  {
    return m_resistance;
  }
  return 0;
}


int DamageHandler::applyBonusDamage(
    BoardSlot &_defender,
    BoardSlot &_attacker,
    const PTCG::ORDER &_order)
{


  if(_order==PTCG::ORDER::AFTER)
  {
    return std::max(0,_attacker.getBonusAfter()-_defender.getReductionAfter());
  }
  else
  {
    return std::max(0,_attacker.getBonusBefore()-_defender.getReductionBefore());
  }
  return 0;

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

