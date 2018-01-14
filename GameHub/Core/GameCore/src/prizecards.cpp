#include "prizecards.h"
#include <algorithm>

PrizeCards::PrizeCards (const PrizeCards &_original)
{
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    m_cards[i].reset(_original.m_cards[i]->clone());
  }
}

Card* PrizeCards::cardAt(const size_t _index)
{
  return m_cards[_index].get();
}

std::array<std::unique_ptr<Card>,6> PrizeCards::view() const
{
  decltype (m_cards) ret;
  for (size_t i = 0; i < m_cards.size(); ++i)
  {
    if(m_cards[i])
      ret[i].reset(m_cards[i]->clone());
  }
  return ret;
}

void PrizeCards::put(std::unique_ptr<Card> &&_card)
{
  // Puts the card in the first free spot
  auto pos = std::find(m_cards.begin(), m_cards.end(), nullptr);
  if (pos != m_cards.end())
  {
    pos->reset(_card.release());
  }
}

size_t PrizeCards::numCards() const
{
  // Get all non-null cards
  static constexpr auto filter = [](const auto& card)->bool { return card.get(); };
  return static_cast<size_t>(std::count_if(m_cards.begin(), m_cards.end(), filter));
}

std::unique_ptr<Card> PrizeCards::take(const size_t _index)
{
  return std::move(m_cards[_index]);
}
