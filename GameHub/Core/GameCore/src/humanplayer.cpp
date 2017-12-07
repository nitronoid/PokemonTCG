#include "humanplayer.h"

Player* HumanPlayer::clone() const
{
  return new HumanPlayer(*this);
}

std::vector<std::unique_ptr<Card>> HumanPlayer::chooseCard(
    const PTCG::PLAYER _player,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned ammount)
{
  std::vector<std::unique_ptr<Card>> foo(static_cast<size_t>(ammount));
  return foo;
}

std::pair<bool, unsigned> HumanPlayer::turn()
{
  return {false, 0};
}
