#include "boardslot.h"
#include "typeinfo"

BoardSlot::BoardSlot(const BoardSlot &_original) :
  m_pokemon(new PokemonCard(*_original.m_pokemon)),
  m_conditions(_original.m_conditions),
  m_tool(new TrainerCard(*_original.m_tool)),
  m_damage(_original.m_damage),
  m_turnPlayed(_original.m_turnPlayed)
{
  for (const auto &eCard : _original.m_energy)
  {
    m_energy.emplace_back(new EnergyCard(*eCard));
  }

  for (const auto &pCard : _original.m_basePokemons)
  {
    m_basePokemons.emplace_back(new PokemonCard(*pCard));
  }
}

void BoardSlot::setDamage(const int _value)
{
    m_damage = _value;
}

void BoardSlot::addCondition(const PTCG::CONDITION _condition)
{
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
        m_pokemon.reset(ptr);
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

std::vector<std::unique_ptr<PokemonCard> > BoardSlot::detachPokemon()
{
    return std::move(m_pokemon);
}

std::unique_ptr<EnergyCard> BoardSlot::detachEnergy(const unsigned _index)
{
    if (_index > m_energy.size() - 1) return nullptr;
    std::unique_ptr<EnergyCard> temp = std::move(m_energy[_index]);
    m_energy.erase(m_energy.begin() + _index);
    return temp;
}

std::unique_ptr<TrainerCard> BoardSlot::detachTool()
{
    return std::move(m_tool);
}

void BoardSlot::setPokemon(std::unique_ptr<PokemonCard> &&_pokemon)
{
    m_pokemon = std::move(_pokemon);
}

const std::unique_ptr<PokemonCard>& BoardSlot::pokemon() const
{
  return m_pokemon;
}

std::unordered_multiset<PTCG::TYPE> BoardSlot::energy() const
{
  return m_energy;
}


