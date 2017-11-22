#ifndef HUB_H
#define HUB_H

#include <iostream>
#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
#include "cardfactory.h"

class Game
{
public:
  Game() = default;
  Game(const Game &_original)
//    m_playerOne(_original.m_playerOne->clone()),
//    m_playerTwo(_original.m_playerTwo->clone())
  {}
  Game clone() const;
  void dealDamage(const int _damage);

private:
  std::unique_ptr<Player> m_playerOne;
  std::unique_ptr<Player> m_playerTwo;
  std::unordered_set<PTCG::TRAINER> m_playableCards;
  std::unique_ptr<Player>* m_currentPlayer = &m_playerOne;
  PTCG::PHASE m_turnPhase;
  unsigned m_turnCount;

};

#endif // HUB_H
