#include "deck.h"
#include <algorithm>

Deck::Deck (const Deck &_original)
{
  m_cards.reserve(_original.m_cards.size());
  for (const auto &card : _original.m_cards)
  {
    m_cards.emplace_back(card->clone());
  }
}

std::vector<std::unique_ptr<Card>> Deck::view()
{
    std::vector<std::unique_ptr<Card>> ret;
    ret.reserve(m_cards.size());
    for (const auto & card : m_cards)
    {
        ret.emplace_back(card->clone());
    }
    return ret;
}

void Deck::shuffle()
{
    static std::random_device seed;
    static std::mt19937_64 gen(seed());
    std::cout<<"Deck Shuffled."<<'\n';
    std::shuffle(m_cards.begin(),m_cards.end(),gen);
}

void Deck::put(std::unique_ptr<Card> &&_card)
{
    m_cards.push_back(std::move(_card));
    std::cout<<_card->getName()<<" has been put into the deck."<<'\n';
}

std::unique_ptr<Card> Deck::take(const unsigned _index)
{
    if (_index > m_cards.size() - 1) return nullptr;
    std::unique_ptr<Card> temp = std::move(m_cards[_index]);
    m_cards.erase(m_cards.begin() + _index);
    return temp;
}

std::unique_ptr<Card> Deck::takeTop()
{
  std::cout<<"Taking card from top of deck."<<'\n';
  return take(m_cards.size() - 1);
}


