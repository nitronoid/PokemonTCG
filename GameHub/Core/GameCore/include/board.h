#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include "hand.h"
#include "prizecards.h"
#include "discardpile.h"
#include "bench.h"

struct Board
{
  /// @brief default ctor
  Board() = default;
  /// @brief default copy ctor
  Board(const Board&) = default;
  /// @brief default assignment operator
  Board& operator=(const Board&) = default;

  /// @brief bench on this player's board
  Bench m_bench;
  /// @brief prize cards of this player's board
  PrizeCards m_prizeCards;
  /// @brief hand of this player's board
  Hand m_hand;
  /// @brief deck of this player's board
  Deck m_deck;
  /// @brief discard pile
  DiscardPile m_discardPile;
};

#endif // BOARD_H
