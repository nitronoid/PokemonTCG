#include "bench.h"

BoardSlot* Bench::slotAt(const unsigned _index)
{
    if(_index>5) return nullptr;
    return &m_slots[_index];
}

const std::unique_ptr<PokemonCard>* active()
{
    return m_slots[0].active();
}

void Bench::put(std::unique_ptr<Card> &&_card, const unsigned _index)
{
    if(_index<5) m_slots[_index] = std::move(_card);
}

std::vector<std::unique_ptr<Card>> Bench::take(const unsigned _index)
{
    std::vector<std::unique_ptr<Card> ret;
    if(_index>5) return ret;

    for(auto& pokemon : m_slots[index].detachPokemon())
    {
        ret.emplace_back(pokemon.release());
    }
    for(auto& energy : m_slots[index].detachEnergy())
    {
        ret.emplace_back(energy.release());
    }
    if(auto ptr = m_slots[index].detachTool())
    {
        ret.emplace_back(ptr.release());
    }
    return std::move(ret);
}

unsigned Bench::numBenched() const
{
    int count = 0;
    for (const auto& slot : m_slots)
    {
        if (slot.active()) ++count;
    }
    return count;
}
