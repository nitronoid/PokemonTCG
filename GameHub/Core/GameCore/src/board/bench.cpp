#include "board/bench.h"

BoardSlot* Bench::slotAt(const size_t _index)
{
  if(_index>5) return nullptr;
  return &m_slots[_index];
}

Status* Bench::activeStatus()
{
  return &m_activeStatus;
}

const Status *Bench::activeStatus() const
{
  return &m_activeStatus;
}

PokemonCard* Bench::active()
{
  return m_slots[0].active();
}

std::array<BoardSlot, 6> Bench::view() const
{
  std::array<BoardSlot,6> ret;
  for (size_t i =0 ; i < 6 ; ++i)
  {
    ret[i]=m_slots[i];
  }
  return ret;
}

void Bench::switchActive(const size_t &_sub)
{
  //using rend to simplify index finding for the substitute
  std::cout<<"Switching to : "<<m_slots.at(_sub).active()->getName()<<'\n';
  /*auto temp = m_slots[0];
  m_slots[0] = std::move(m_slots[_sub]);
  m_slots[_sub] = std::move(temp);*/
  m_slots[0].swap(m_slots[_sub]);
  m_activeStatus.removeAllConditions();
}

void Bench::put(std::unique_ptr<Card> &&_card, const size_t _index)
{
  if(_index<5)
  {
    m_slots[_index].attachCard(std::move(_card));
  }
}

std::vector<std::unique_ptr<Card>> Bench::take(const size_t _index)
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