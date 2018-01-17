#include "board.h"

Board::Board(const Board&_original) :
  m_bench(_original.m_bench)
{
  *deck() = *_original.deck();
  *hand() = *_original.hand();
  *prizeCards() = *_original.prizeCards();
  *discardPile() = *_original.discardPile();
}


Board& Board::operator=(const Board&_original)
{
  m_bench = _original.m_bench;
  *deck() = *_original.deck();
  *hand() = *_original.hand();
  *prizeCards() = *_original.prizeCards();
  *discardPile() = *_original.discardPile();
  return *this;
}

CardPile* Board::pile(const PTCG::PILE _pile)
{
  return m_piles[static_cast<size_t>(_pile)].get();
}

const CardPile* Board::pile(const PTCG::PILE _pile) const
{
  return m_piles[static_cast<size_t>(_pile)].get();
}

Deck* Board::deck()
{
  return static_cast<Deck*>(pile(PTCG::PILE::DECK));
}

Hand* Board::hand()
{
  return static_cast<Hand*>(pile(PTCG::PILE::HAND));
}

DiscardPile* Board::discardPile()
{
  return static_cast<DiscardPile*>(pile(PTCG::PILE::DISCARD));
}

PrizeCards* Board::prizeCards()
{
  return static_cast<PrizeCards*>(pile(PTCG::PILE::PRIZE));
}

const Deck* Board::deck() const
{
  return static_cast<const Deck*>(pile(PTCG::PILE::DECK));
}

const Hand* Board::hand() const
{
  return static_cast<const Hand*>(pile(PTCG::PILE::HAND));
}

const DiscardPile* Board::discardPile() const
{
  return static_cast<const DiscardPile*>(pile(PTCG::PILE::DISCARD));
}

const PrizeCards* Board::prizeCards() const
{
  return static_cast<const PrizeCards*>(pile(PTCG::PILE::PRIZE));
}


