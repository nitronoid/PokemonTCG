#include "prizecards.h"


PrizeCards::PrizeCards (const PrizeCards &_original)
{
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    m_cards[i].reset(_original.m_cards[i]->clone());
  }
}

std::array<std::unique_ptr<Card>,6> PrizeCards::view() const
{
  std::array<std::unique_ptr<Card>,6> ret;
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    if(m_cards.at(i) != nullptr)
    {
      std::cout<<"Card ID: "<<m_cards.at(i)->getID()<<" Card Name: "<<m_cards.at(i)->getName()<<'\n';
      ret.at(i).reset(m_cards.at(i)->clone());
    }
    else
    {
      ret.at(i) = nullptr;
    }
  }
  return ret;
}

void PrizeCards::put(std::unique_ptr<Card> &&)
{
  //dont do anything
}

std::unique_ptr<Card> PrizeCards::take(const size_t _index)
{
  if (_index > m_cards.size() - 1) return nullptr;
  return std::move(m_cards[_index]);
}
