#include "boardslot.h"
#include <typeinfo>
#include <algorithm>

BoardSlot::BoardSlot(const BoardSlot &_original) :
    m_conditions(_original.m_conditions),
    m_tool(new TrainerCard(*_original.m_tool)),
    m_damage(_original.m_damage),
    m_turnPlayed(_original.m_turnPlayed)
{
    for (const auto &eCard : _original.m_energy)
    {
        m_energy.emplace_back(new EnergyCard(*eCard));
    }

    for (const auto &pCard : _original.m_pokemon)
    {
        m_pokemon.emplace_back(new PokemonCard(*pCard));
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
    std::vector<std::unique_ptr<PokemonCard>> ret;
    while(!m_pokemon.empty())
    {
        auto last = m_pokemon.end() - 1;
        ret.emplace_back(last->release());
        m_pokemon.erase(last);
    }
    return ret;
}

std::unique_ptr<PokemonCard> BoardSlot::devolvePokemon()
{
    if(m_pokemon.empty()) return nullptr;
    auto last = m_pokemon.end() - 1;
    std::unique_ptr<PokemonCard> ret(last->release());
    m_pokemon.erase(last);
    return std::move(ret);
}

std::vector<std::unique_ptr<EnergyCard>> BoardSlot::detachEnergy()
{
    std::vector<std::unique_ptr<EnergyCard>> ret;
    for(auto& energy: m_energy)
    {
        ret.emplace_back(energy.release());
    }
    m_energy.clear();
    return ret;
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
    m_pokemon.emplace_back(std::move(_pokemon));
}

const std::unique_ptr<PokemonCard>* BoardSlot::active() const
{
    return &m_pokemon[m_pokemon.size() - 1];
}

BoardSlot::TypeMSet BoardSlot::energy() const
{
    BoardSlot::TypeMSet ret;
    std::for_each(m_energy.begin(), m_energy.end(), [&ret](const auto & eCard)
    {
        ret.insert(eCard->type());
    }
    );
    return ret;
}


