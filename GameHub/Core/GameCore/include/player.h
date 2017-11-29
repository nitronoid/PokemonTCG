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
#include <tuple>

class Player
{
public:
  Player(const Player&) = default;
  Player(Game& _parentGame) :
    m_parentGame(_parentGame)
  {}

  virtual Player* clone() const = 0;

  virtual std::vector<std::unique_ptr<Card>> chooseCard(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned ammount
                     ) = 0;
  virtual std::pair<bool, std::string> turn() = 0;

protected:
  void playCard(const unsigned _index);
  void retreat(const unsigned _replacement);
  const std::vector<std::unique_ptr<Card>>& viewHand() const;
  const std::vector<std::unique_ptr<Card>>& viewDiscard(const PTCG::PLAYER _owner = PTCG::PLAYER::SELF) const;
  const std::array<std::unique_ptr<Card>, 6>& viewBoard(const PTCG::PLAYER _owner = PTCG::PLAYER::SELF) const;

  Game getDummyGame() const;

private:
  bool m_canRetreat = true;
  Game& m_parentGame;
};

#endif // PLAYER_H
