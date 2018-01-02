#include "damagehandler.h"

bool DamageHandler::heal(BoardSlot *_slot, const unsigned &_value)
{
  if(_slot->getDamage()>0)
  {
      _slot->removeDamage(_value);
      return true;
  }
  std::cout<<"Full Health, this does nothing"<<'\n';
  return false;

}

void DamageHandler::generalDamage(
    BoardSlot *_defender,
    BoardSlot *_attacker,
    const bool &_isBenched,
    const unsigned &_damage)
{
    int totalDamage;
    //If this is an active pokemon:
    if(_isBenched == 0)
    {
        int weakRes = applyWeakRes(_defender,_attacker);
        //if it says -20, it's resistance and 2 for weakness multiplier
        if(weakRes<=0)
        {
            totalDamage =
                _damage +
                applyBonusDamage(_defender, _attacker, PTCG::ORDER::BEFORE) +
                weakRes +
                applyBonusDamage(_defender, _attacker,PTCG::ORDER::AFTER);
                _defender->takeDamage(std::max(0,totalDamage));
        }
        else
        {
            totalDamage =
                (_damage +
                applyBonusDamage(_defender, _attacker, PTCG::ORDER::BEFORE)) *
                weakRes +
                applyBonusDamage(_defender, _attacker, PTCG::ORDER::AFTER);
                _defender->takeDamage(std::max(0,totalDamage));
        }
    }
    else //if target is bench
    {
      totalDamage =
          _damage +
          applyBonusDamage(_defender, _attacker, PTCG::ORDER::BEFORE) +
          applyBonusDamage(_defender, _attacker, PTCG::ORDER::AFTER);
          _defender->takeDamage(std::max(0,totalDamage));
    }


}

void DamageHandler::rawDamage(BoardSlot* _defender, const unsigned &_damage)
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


int DamageHandler::applyBonusDamage(BoardSlot* _defender, BoardSlot* _attacker, const PTCG::ORDER &_order)
{

  if(_order==PTCG::ORDER::AFTER)
  {
    return _attacker->getBonusAfter() - _defender->getReductionAfter();
  }
  else
  {
    return _attacker->getBonusBefore() - _defender->getReductionBefore();
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

