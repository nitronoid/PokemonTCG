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
  Game(const Game &_original) :
    m_playableCards(_original.m_playableCards),
    m_turnPhase(_original.m_turnPhase),
    m_turnCount(_original.m_turnCount)
  {
    for (size_t i = 0; i < m_players.size(); ++i)
    {
      if (_original.m_players[i]) m_players[i].reset( _original.m_players[i]->clone());
    }
  }
  Game clone() const;
  void dealDamage(const int _damage);
  void endTurn();
  void play();

private:
  std::array<std::unique_ptr<Player>, 2> m_players;
  std::unordered_set<PTCG::TRAINER> m_playableCards;
  PTCG::PHASE m_turnPhase;
  unsigned m_turnCount;
  bool m_turnFinished;

};

#endif // HUB_H
