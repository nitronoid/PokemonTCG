#include "prizecards.h"


PrizeCards::PrizeCards (const PrizeCards &_original)
{
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    m_cards[i].reset(_original.m_cards[i]->clone());
  }
}

const std::array<std::unique_ptr<Card>, 6> &PrizeCards::view()
{
    return m_cards;
}

void PrizeCards::put(std::unique_ptr<Card> &&)
{
    //dont do anything
}

std::unique_ptr<Card> PrizeCards::take(const unsigned _index)
{
    if (_index > m_cards.size() - 1) return nullptr;
    return std::move(m_cards[_index]);
}
