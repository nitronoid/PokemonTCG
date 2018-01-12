#include "discardpile.h"


DiscardPile::DiscardPile (const DiscardPile &_original)
{
  m_cards.reserve(_original.m_cards.size());
  for (const auto& card : _original.m_cards)
  {
    m_cards.emplace_back(card->clone());
  }
}

DiscardPile& DiscardPile::operator=(const DiscardPile&_original)
{
  m_cards.reserve(_original.m_cards.size());
  for (const auto &card : _original.m_cards)
  {
    m_cards.emplace_back(card->clone());
  }
  return *this;
}

Card* DiscardPile::cardAt(const size_t _index)
{
  return m_cards[_index].get();
}

std::vector<std::unique_ptr<Card>> DiscardPile::view() const
{
  std::vector<std::unique_ptr<Card>> ret;
  ret.reserve(m_cards.size());
  for (const auto & card : m_cards)
  {
    std::cout<<"Card ID: "<<card->getID()<<"Card Name: "<<card->getName()<<'\n';
    ret.emplace_back(card->clone());
  }
  return ret;
}

void DiscardPile::put(std::unique_ptr<Card> &&_card)
{
  std::cout<<_card->getName()<<" has been discarded."<<'\n';
  m_cards.push_back(std::move(_card));
}

std::unique_ptr<Card> DiscardPile::take(const size_t _index)
{
  if (_index > m_cards.size() - 1) return nullptr;
  std::unique_ptr<Card> temp = std::move(m_cards[_index]);
  m_cards.erase(m_cards.begin() + _index);
  return temp;
}

size_t DiscardPile::numCards() const
{
  return m_cards.size();
}
