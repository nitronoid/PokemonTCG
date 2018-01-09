#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include "hand.h"
#include "prizecards.h"
#include "discardpile.h"
#include "bench.h"

struct Board
{
  Board() = default;
  Board(const Board&) = default;
  Board& operator=(const Board&) = default;

  Bench m_bench;
  PrizeCards m_prizeCards;
  Hand m_hand;
  Deck m_deck;
  DiscardPile m_discardPile;
};

#endif // BOARD_H
