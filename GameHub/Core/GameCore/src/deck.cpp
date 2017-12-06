#include "deck.h"



Deck::Deck (const Deck &_original)
{
  for (const auto &card : _original.m_cards)
  {
    m_cards.emplace_back(card->clone());
  }
}

std::vector<std::unique_ptr<Card>> Deck::view()
{
    std::vector<std::unique_ptr<Card>> ret;
    for (const auto & card : m_cards)
    {
        ret.emplace_back(card->clone());
    }
    return ret;
}

void Deck::shuffle()
{
    static std::mt19937_64 gen(m_seed);

}

void Deck::put(std::unique_ptr<Card> &&_card, const unsigned _index)
{
    m_cards.emplace_back(std::move(_card));
    std::shuffle(m_cards.begin(),m_cards.end(),gen);
}

std::unique_ptr<Card> Deck::take(const unsigned _index)
{
    if (_index > m_cards.size() - 1) return nullptr;
    std::unique_ptr<Card> temp = std::move(m_cards[_index]);
    m_cards.erase(m_cards.begin() + _index);
    return temp;
}
