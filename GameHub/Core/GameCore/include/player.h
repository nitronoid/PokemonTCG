#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "board.h"
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

  virtual ~Player();

  virtual Player* clone() const = 0;

  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;

  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) = 0;

  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) = 0;

  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;

  virtual bool agree(const PTCG::ACTION _action) = 0;

  virtual std::pair<bool, unsigned> turn() = 0;

protected:
  void playCard(const unsigned _index);
  void retreat();
  std::vector<std::unique_ptr<Card>> viewHand() const;
  std::vector<std::unique_ptr<Card>> viewDiscard(const PTCG::PLAYER &_owner = PTCG::PLAYER::SELF) const;
  std::array<BoardSlot, 6> viewBench(const PTCG::PLAYER &_owner = PTCG::PLAYER::SELF) const;

  Game getDummyGame() const;

private:
  bool m_canRetreat = true;
  Game& m_parentGame;
};

#endif // PLAYER_H
