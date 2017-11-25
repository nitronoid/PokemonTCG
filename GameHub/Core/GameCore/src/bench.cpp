#include "bench.h"

void Bench::put(std::unique_ptr<Card> &&_card)
{

}

std::unique_ptr<Card> Bench::take(const unsigned _index)
{
  //TODO: Remove all other cards from the slot?
  return std::move(m_slots[_index].detachPokemon());
}

BoardSlot& Bench::slotAt(const unsigned _index)
{
  return m_slots[_index];
}

unsigned Bench::numBenched() const
{
  int count = 0;
  for (const auto& slot : m_slots)
  {
    if (slot.pokemon()) ++count;
  }
  return count;
}
