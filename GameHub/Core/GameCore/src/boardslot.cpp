#include "boardslot.h"
#include <typeinfo>
#include <algorithm>

BoardSlot::BoardSlot(const BoardSlot &_original) :
  m_conditions(_original.m_conditions),
  m_tool(new TrainerCard(*_original.m_tool)),
  m_damageTaken(_original.m_damageTaken),
  m_turnPlayed(_original.m_turnPlayed)
{
  m_energy.reserve(_original.m_energy.size());
  for (const auto &eCard : _original.m_energy)
  {
    m_energy.emplace_back(new EnergyCard(*eCard));
  }

  m_pokemon.reserve(_original.m_pokemon.size());
  for (const auto &pCard : _original.m_pokemon)
  {
    m_pokemon.emplace_back(new PokemonCard(*pCard));
  }
}

void BoardSlot::takeDamage(const int _damage)
{
  std::cout<<"Taking "<<_damage<<" damage."<<'\n';
  m_damageTaken += _damage;
}

void BoardSlot::setDamage(const int _value)
{
  std::cout<<"Damage taken set to: "<<_value<<'\n';
  m_damageTaken = _value;
}

void BoardSlot::addCondition(const PTCG::CONDITION _condition)
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

void BoardSlot::removeCondition(const PTCG::CONDITION _condition)
{
  m_conditions.erase(_condition);
}

void BoardSlot::removeAllConditions()
{
  m_conditions.clear();
}

void BoardSlot::attachCard(std::unique_ptr<Card> &&_card)
{
  Card* raw = _card.release();
  if(auto ptr = dynamic_cast<PokemonCard*>(raw))
  {
    m_pokemon.emplace_back(ptr);
  }
  else if(auto ptr = dynamic_cast<EnergyCard*>(raw))
  {
    m_energy.emplace_back(ptr);
  }
  else if(auto ptr = dynamic_cast<TrainerCard*>(raw))
  {
    m_tool.reset(ptr);
  }
}

std::vector<std::unique_ptr<PokemonCard>> BoardSlot::detachPokemon()
{
  std::vector<std::unique_ptr<PokemonCard>> ret = std::move(m_pokemon);
  return ret;
}

std::unique_ptr<PokemonCard> BoardSlot::devolvePokemon()
{
  if(m_pokemon.empty()) return nullptr;
  auto last = m_pokemon.end() - 1;
  std::unique_ptr<PokemonCard> ret(last->release());
  m_pokemon.erase(last);
  return ret;
}

std::vector<std::unique_ptr<EnergyCard>> BoardSlot::detachEnergy()
{
  std::vector<std::unique_ptr<EnergyCard>> ret = std::move(m_energy);
  return ret;
}

std::unique_ptr<EnergyCard> BoardSlot::detachEnergy(const unsigned _index)
{
  if (_index > m_energy.size() - 1) return nullptr;
  std::unique_ptr<EnergyCard> temp(m_energy[_index].release());
  m_energy.erase(m_energy.begin() + _index);
  return temp;
}

std::unique_ptr<TrainerCard> BoardSlot::detachTool()
{
  return std::move(m_tool);
}

void BoardSlot::setPokemon(std::unique_ptr<PokemonCard> &&_pokemon)
{
  m_pokemon.push_back(std::move(_pokemon));
}

PokemonCard *BoardSlot::active() const
{
  return m_pokemon[m_pokemon.size() - 1].get();
}

BoardSlot::TypeMSet BoardSlot::energy() const
{
  BoardSlot::TypeMSet ret;
  ret.reserve(m_energy.size());
  std::for_each(m_energy.begin(), m_energy.end(), [&ret](const auto & eCard)
  {
    ret.insert(eCard->type());
  }
  );
  return ret;
}


