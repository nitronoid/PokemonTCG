#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "bench.h"
#include "hand.h"
#include "deck.h"
#include "discardpile.h"
#include "prizecards.h"
#include <vector>
#include <memory>

class Player
{
public:
  Player(const Player&) = default;
  Player(Game& _parentGame) :
    m_parentGame(_parentGame)
  {}

  virtual Player* clone() const = 0;

public:
  virtual std::vector<std::unique_ptr<Card>> chooseCard(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned ammount,
      const PTCG::ACTION _action
                     ) = 0;
  virtual void turn() = 0;

protected:
  void playCard(const unsigned _index);
  void attack(const std::string &_name);
  void endTurn() const;
  void retreat(const unsigned _replacement);
  void viewHand() const;
  void viewBench() const;

  Game getDummyGame() const;

private:
  BoardSlot m_activePokemon;
  Bench m_bench;
  Hand m_hand;
  Deck m_deck;
  PrizeCards m_prizeCards;
  DiscardPile m_discardPile;
  bool m_canRetreat = true;
  Game& m_parentGame;
};

#endif // PLAYER_H
