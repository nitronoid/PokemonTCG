#include "humanplayer.h"

Player* HumanPlayer::clone() const
{
  return new HumanPlayer(*this);
}

std::vector<std::unique_ptr<Card>> HumanPlayer::chooseCard(
    const PTCG::PLAYER _player,
    const PTCG::PILE _origin,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned ammount,
    const PTCG::ACTION _action)
{
  return std::vector<std::unique_ptr<Card>>{};
}

void HumanPlayer::turn()
{

}
