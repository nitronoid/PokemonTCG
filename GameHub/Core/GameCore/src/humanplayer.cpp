#include "humanplayer.h"
#include <time.h>
#include <random>

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
  srand((unsigned)time(NULL));
  playCard((int)rand%(int)(viewHand().size()));
  bool temp= ((int)rand()%2 == 0 ? true : false);
  unsigned choice=0;
  do{
    choice=(unsigned)(rand()%counter);
  }while(viewBench().at(choice) != nullptr);
  return std::pair<bool, unsigned> {temp,choice};
}
