#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
public:
  HumanPlayer(const HumanPlayer&) = default;
  HumanPlayer(HumanPlayer& _parentGame) :
    Player(_parentGame)
  {}

  virtual Player* clone() const
  {
    return new HumanPlayer(*this);
  }
};


#endif // HUMANPLAYER_H
