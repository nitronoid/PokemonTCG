#include "hand.h"

Hand::Hand (const Hand &_original)
{
  m_cards.reserve(_original.m_cards.size());
  for (const auto &card : _original.m_cards)
  {
    m_cards.emplace_back(card->clone());
  }
}

std::vector<std::unique_ptr<Card>> Hand::view()const
{
  std::vector<std::unique_ptr<Card>> ret;
  ret.reserve(m_cards.size());
  for (const auto & card : m_cards)
  {
    ret.emplace_back(card->clone());
  }
  return ret;
}

void Hand::put(std::unique_ptr<Card> &&_card)
{
  std::cout<<_card->getName()<<" has been put into the hand."<<'\n';
  m_cards.push_back(std::move(_card));
}


std::unique_ptr<Card> Hand::take(const size_t _index)
{
  if (_index > m_cards.size() - 1) return nullptr;
  std::unique_ptr<Card> temp = std::move(m_cards[_index]);
  m_cards.erase(m_cards.begin() + _index);
  return temp;
}

void Hand::filler(Card _card)
{
  std::unique_ptr<Card> card = std::unique_ptr<Card>(_card);
  std::fill(m_cards.begin(),m_cards.end(),card);
}
