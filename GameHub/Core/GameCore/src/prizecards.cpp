#include "prizecards.h"

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
