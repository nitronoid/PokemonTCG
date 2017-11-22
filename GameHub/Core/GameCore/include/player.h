#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

class Player
{
public:
  Player(const Player&) = default;
  Player(Game& _parentGame) :
    m_parentGame(_parentGame)
  {}

  void playCard(const unsigned _index);
  void attack(const unsigned _index);
  void endTurn() const;
  void retreat(const unsigned _replacement);
  void viewHand() const;
  void viewBench() const;


  Game getDummyGame() const;

private:
  bool m_canRetreat = true;
  Game& m_parentGame;
};

#endif // PLAYER_H