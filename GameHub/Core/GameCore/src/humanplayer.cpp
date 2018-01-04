#include "humanplayer.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>

Player* HumanPlayer::clone() const
{
  return new HumanPlayer(*this);
}

std::string actionStr(const PTCG::ACTION _action)
{
  using act = PTCG::ACTION;
  std::string ret;
  switch (_action)
  {
    case act::DRAW:    { ret = "draw"; break; }
    case act::DISCARD: { ret = "discard"; break; }
    case act::PLAY:    { ret = "play"; break; }
    case act::VIEW:    { ret = "view"; break; }
    case act::MOVE:    { ret = "move"; break; }
    case act::HEAL:    { ret = "heal"; break; }
  }
  return ret;
}

std::string pileStr(const PTCG::PILE _origin)
{
  using pile = PTCG::PILE;
  std::string ret;
  switch (_origin)
  {
    case pile::DECK:    { ret = "deck"; break; }
    case pile::DISCARD: { ret = "discard"; break; }
    case pile::HAND:    { ret = "hand"; break; }
    case pile::PRIZE:   { ret = "prize"; break; }
  }
  return ret;
}

std::vector<size_t> HumanPlayer::chooseCards(
    const PTCG::PLAYER _player,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount)
{
  std::vector<size_t> choice;
  std::unordered_set<size_t> picked;
  while (choice.size() < _amount)
  {
    size_t len = _options.size();
    size_t pick  = len;
    bool err = false;
    while (pick > (len -1) || err)
    {
      std::string owner = "";
      if (_player == PTCG::PLAYER::ENEMY) owner = " enemies ";
      std::cout<<"Pick a card from 0 - "<<len-1<<", to "<<actionStr(_action)<<" from your "<<owner<<pileStr(_origin)<<": ";
      std::cin>>pick;
      err = std::cin.fail() || picked.count(pick);
      if (err) std::cout<<"Please enter an int.\n";
      else
      {
        choice.push_back(pick);
        picked.insert(pick);
      }
    }
  }
  return choice;
}

std::vector<size_t> HumanPlayer::chooseSlot(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

void HumanPlayer::learnCards(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const std::vector<size_t> &_indices,
    const std::vector<std::unique_ptr<Card>> &_revealed
    )
{}

std::vector<size_t> HumanPlayer::chooseEnergy(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _destination,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card> > &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

bool HumanPlayer::agree(const PTCG::ACTION _action)
{
  return true;
}

bool randomBool()
{
  static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
  return gen();
}

std::pair<bool, unsigned> HumanPlayer::turn()
{
  // Random engine
  static std::random_device seed;
  static std::mt19937_64 eng(seed());

  // Play random card from hand
  std::uniform_int_distribution<unsigned> hgen(0, static_cast<unsigned>(viewHand().size() - 1));
  playCard(hgen(eng));

  // Should we attack?
  bool doAttack = randomBool();

  // Play random card from hand
  unsigned attackNum = viewBench().at(0).active()->attackNum();
  std::uniform_int_distribution<unsigned> agen(0, attackNum - 1);

  // Return the decision
  return std::pair<bool, unsigned> {doAttack, agen(eng)};
}
