#include "deck.h"

const std::vector<std::unique_ptr<Card>>& Deck::view()
{
    return m_cards;
}

void Deck::shuffle()
{

}

void Deck::put(std::unique_ptr<Card> &&_card)
{
    m_cards.emplace_back(std::move(_card));
}

std::unique_ptr<Card> Deck::take(const unsigned _index)
{
    if (_index > m_cards.size() - 1) return nullptr;
    std::unique_ptr<Card> temp = std::move(m_cards[_index]);
    m_cards.erase(m_cards.begin() + _index);
    return temp;
}