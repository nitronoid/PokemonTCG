#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
public:
  HumanPlayer(const HumanPlayer&) = default;
  HumanPlayer(Game& _parentGame) :
    Player(_parentGame)
  {}

  virtual Player* clone() const override;

  virtual std::vector<size_t> chooseCards(const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;

  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) override;

  virtual std::pair<bool, unsigned> turn() override;

};


#endif // HUMANPLAYER_H
