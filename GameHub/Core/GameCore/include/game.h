#ifndef HUB_H
#define HUB_H

#include <iostream>
#include <unordered_set>
#include "pokemoncard.h"
#include "player.h"
#include "cardpool.h"

class Game
{
public:
  Game clone() const;

  void dealDamage(const int _damage);

private:
  Player m_playerOne {*this};
  Player m_playerTwo {*this};
  std::unordered_set<PTCG::TRAINER> m_playableCards;
  Player* m_currentPlayer;
  PTCG::PHASE m_turnPhase;
  unsigned m_turnCount;

};

#endif // HUB_H
