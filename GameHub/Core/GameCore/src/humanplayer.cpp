#include "humanplayer.h"

Player* HumanPlayer::clone() const
{
  return new HumanPlayer(*this);
}

std::vector<std::unique_ptr<Card>> HumanPlayer::chooseCard(const PTCG::PLAYER _player,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned ammount)
{
  return std::vector<std::unique_ptr<Card>>{};
}

std::pair<bool, std::string> HumanPlayer::turn()
{

}
