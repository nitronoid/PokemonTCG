#include "prizecards.h"


PrizeCards::PrizeCards (const PrizeCards &_original)
{
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    m_cards[i].reset(_original.m_cards[i]->clone());
  }
}

std::vector<std::unique_ptr<Card>> PrizeCards::view() const
{
    std::vector<std::unique_ptr<Card>> ret;
    ret.reserve(6);
    for (size_t i = 0; i < m_cards.size(); ++i)
    {
        ret[i].reset(m_cards[i]->clone());
    }
    return ret;
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
