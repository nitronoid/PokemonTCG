#include "damagehandler.h"

bool DamageHandler::heal(Bench &_bench,
                         const unsigned &_benchIndex,
                         const unsigned &_value)
{
  if(_bench.view().at(_benchIndex)->getDamage()>0)
  {
      //lazy implementation, decrease damage taken = healing
      _bench.view().at(_benchIndex)->takeDamage(-_value);
      return true;
  }
  std::cout<<"Full Health, this does nothing"<<'\n';
  return false;

}

void DamageHandler::generalDamage(std::array<Bench,2> &_bench,
                                     const unsigned &_turnCount,
                                     const unsigned &_defenderIndex,
                                     const unsigned &_damage)
{

    unsigned totalDamage;
    //BoardSlot defender = _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex);
    int weakRes = applyWeakRes(_bench,_turnCount);
    //If this is an active pokemon:
    if(_defenderIndex == 0)
    {
        if(weakRes<=0)
        {
            totalDamage =
                _damage                               +
                applyBonusDamage(_bench,
                                 _turnCount,
                                 _defenderIndex,
                                 PTCG::ORDER::BEFORE) +
                weakRes                               +
                applyBonusDamage(_bench,
                                 _turnCount,
                                 _defenderIndex,
                                 PTCG::ORDER::AFTER);


                _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
        }
        else
        {
            totalDamage =
                (
                _damage                                +
                applyBonusDamage(_bench,
                                 _turnCount,
                                 _defenderIndex,
                                 PTCG::ORDER::BEFORE)) *
                weakRes                                +
                applyBonusDamage(_bench,
                                 _turnCount,
                                 _defenderIndex,
                                 PTCG::ORDER::AFTER);

                _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
        }
    }
    else //if target is bench
    {
      totalDamage = _damage                               +
          applyBonusDamage(_bench,
                           _turnCount,
                           _defenderIndex,
                           PTCG::ORDER::BEFORE)           +
          applyBonusDamage(_bench,
                           _turnCount,
                           _defenderIndex,
                           PTCG::ORDER::AFTER);


          _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
    }


}

void DamageHandler::rawDamage(Bench &_bench,
                           const unsigned &_defenderIndex,
                           const unsigned &_damage)
{
  std::cout<<"Taking "<<_damage<<" damage from effects."<<'\n';
   _bench.view().at(_defenderIndex)->takeDamage(_damage);
}

int DamageHandler::applyWeakRes(std::array<Bench,2> &_bench,
                                   const unsigned &_turnCount)
{


  if(_bench.at(getAttacker(_turnCount)).view().at(0)->active()->weakness() ==
     _bench.at(getDefender(_turnCount)).view().at(0)->active()->weakness())
  {
    return m_weaknessMult;
  }
  else if (_bench.at(getAttacker(_turnCount)).view().at(0)->active()->resistance() ==
           _bench.at(getDefender(_turnCount)).view().at(0)->active()->resistance())
  {
    return m_resistance;
  }
  return 0;
}


int DamageHandler::applyBonusDamage(std::array<Bench, 2> &_bench,
                                       const unsigned &_turnCount,
                                       const unsigned &_defenderIndex,
                                       const PTCG::ORDER &_order)
{


  if(_order==PTCG::ORDER::AFTER)
  {

      if((_bench.at(getAttacker(_turnCount)).view().at(0)->getBonusAfter()) -
         _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionAfter() < 0)
        {
          return 0;
        }
      return (_bench.at(getAttacker(_turnCount)).view().at(0)->getBonusAfter()) -
          _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionAfter();
  }
  else
  {
      if((_bench.at(getAttacker(_turnCount)).view().at(0)->getBonusBefore()) -
         _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionBefore() < 0)
        {
          return 0;
        }
      return (_bench.at(getAttacker(_turnCount)).view().at(0)->getBonusBefore()) -
          _bench.at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionBefore();
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

