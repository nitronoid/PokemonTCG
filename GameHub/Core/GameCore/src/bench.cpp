#include "bench.h"

BoardSlot* Bench::slotAt(const unsigned _index)
{
  if(_index>5) return nullptr;
  return &m_slots[_index];
}

PokemonCard* Bench::active()
{
  return m_slots[0].active();
}

std::array<BoardSlot, 6> Bench::view() const
{
  std::array<BoardSlot,6> ret;
  for (int i =0 ; i < 6 ; ++i)
  {
      std::cout<<"Number of cards in slot "<< i <<" : "<<m_slots[i].numCards()<<'\n';
      ret[i]=m_slots[i];
  }
  return ret;
}

void Bench::switchActive(const unsigned &_sub)
{
    //using rend to simplify index finding for the substitute
    std::cout<<"Switching to : "<<m_slots.at(_sub).active()->getName()<<'\n';
    std::swap(m_slots[0],m_slots[_sub]);
    slotAt(_sub)->removeAllConditions();
}

void Bench::put(std::unique_ptr<Card> &&_card, const unsigned _index)
{
  if(_index<5)
  {
    m_slots[_index].attachCard(std::move(_card));
  }
}

std::vector<std::unique_ptr<Card>> Bench::take(const unsigned _index)
{
  std::vector<std::unique_ptr<Card>> ret;
  if(_index>5) return ret;
  auto& slot = m_slots[_index];
  ret.reserve(slot.numCards());
  for(auto& pokemon : slot.detachPokemon())
  {
    ret.emplace_back(pokemon.release());
  }
  for(auto& energy : slot.detachEnergy())
  {
    ret.emplace_back(energy.release());
  }
  if(auto tool = slot.detachTool())
  {
    ret.emplace_back(tool.release());
  }
  return ret;
}

unsigned Bench::numBenched() const
{
  unsigned count = 0;
  for (const auto& slot : m_slots)
  {
    if (slot.active()) ++count;
  }
  return count;
}
