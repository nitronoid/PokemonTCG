#ifndef HUB_H
#define HUB_H

#include <memory>
#include <unordered_set>
#include "pokemoncard.h"
#include "humanplayer.h"
#include "cardfactory.h"
#include "board.h"

class Game
{
public:
  Game() = default;
  Game(Game&&_original) = default;
  Game clone() const;
  void dealDamage(const int _damage);
  void start();
  bool canPlay(const std::unique_ptr<Card>& _card);
  bool playCard(const unsigned _index);
  bool drawCard(Board& _board);
  void moveCards(
      const std::vector<int> _cardIndices,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::PILE _destination,
      const bool _reveal
      );
  std::vector<int> playerChoice(
      const PTCG::PLAYER _thinker,
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::CARD _cardType,
      const PTCG::ACTION _action,
      const int _amount,
      const int _range
      );

  std::vector<std::unique_ptr<Card>> viewBoard(const unsigned &_player, const PTCG::PILE _target) const;
  std::unique_ptr<BoardSlot> viewBench(const unsigned &_player, const unsigned &_index) const;
private:
  Game(const Game &_original);

  void nextTurn();
  void setupGame();

  void attack(PokemonCard* _pokemon, const unsigned _index);

private:
  std::array<std::unique_ptr<Player>, 2> m_players;
  std::array<Board, 2> m_boards;
  std::unordered_set<PTCG::CARD> m_playableCards;
  PTCG::PHASE m_turnPhase = PTCG::PHASE::NONE;
  unsigned m_turnCount = 0;
  bool m_turnFinished = false;
  bool m_rulesBroken = false;
  bool m_gameFinished = false;

};

#endif // HUB_H
