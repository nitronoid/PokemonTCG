#include "damagecalculator.h"

void DamageCalculator::generalDamage(std::unique_ptr<std::array<Bench,2>> &_bench,
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


                _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
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

                _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
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


          _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(totalDamage);
    }


}


void DamageCalculator::rawDamage(std::unique_ptr<std::array<Bench,2> > &_bench,
                                 const unsigned &_turnCount,
                                 const unsigned &_defenderIndex,
                                 const unsigned &_damage)
{
  _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->takeDamage(_damage);
}



int DamageCalculator::applyWeakRes(std::unique_ptr<std::array<Bench,2>> &_bench,
                                   const unsigned &_turnCount)
{
  //PokemonCard attacker = _bench.get()->at(getAttacker(_turnCount)).view().at(0).active();
  //PokemonCard defender = _bench.get()->at(getDefender(_turnCount)).view().at(0).active();

  if(_bench.get()->at(getAttacker(_turnCount)).view().at(0)->active()->weakness() ==
     _bench.get()->at(getDefender(_turnCount)).view().at(0)->active()->weakness())
  {
    return m_weaknessMult;
  }
  else if (_bench.get()->at(getAttacker(_turnCount)).view().at(0)->active()->resistance() ==
           _bench.get()->at(getDefender(_turnCount)).view().at(0)->active()->resistance())
  {
    return m_resistance;
  }
  return 0;
}


int DamageCalculator::applyBonusDamage(std::unique_ptr<std::array<Bench, 2> > &_bench,
                                       const unsigned &_turnCount,
                                       const unsigned &_defenderIndex,
                                       const PTCG::ORDER &_order)
{


  if(_order==PTCG::ORDER::AFTER)
  {

      if((_bench.get()->at(getAttacker(_turnCount)).view().at(0)->getBonusAfter()) -
         _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionAfter() < 0)
        {
          return 0;
        }
      return (_bench.get()->at(getAttacker(_turnCount)).view().at(0)->getBonusAfter()) -
          _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionAfter();
  }
  else
  {
      if((_bench.get()->at(getAttacker(_turnCount)).view().at(0)->getBonusBefore()) -
         _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionBefore() < 0)
        {
          return 0;
        }
      return (_bench.get()->at(getAttacker(_turnCount)).view().at(0)->getBonusBefore()) -
          _bench.get()->at(getDefender(_turnCount)).view().at(_defenderIndex)->getReductionBefore();
  }
  return 0;

}


void DamageCalculator::increaseBurn(const int _damage)
{
  m_burnDamage+=_damage;
}

void DamageCalculator::increaseConfuse(const int _damage)
{
  m_confuseDamage+=_damage;
}

void DamageCalculator::increasePoison(const int _damage)
{
  m_poisonDamage+=_damage;
}

