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

  virtual std::vector<std::unique_ptr<Card>> chooseCard(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned ammount
      ) override;

  virtual std::pair<bool, std::string> turn() override;

};


#endif // HUMANPLAYER_H
