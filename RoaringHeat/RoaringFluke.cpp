#include "humanplayer.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>




template<typename T>
std::vector<size_t> promptChoice(
    const PTCG::PLAYER _player,
    const std::string &_pile,
    const PTCG::ACTION _action,
    const std::vector<T> &_options,
    const unsigned _amount
    )
{
  std::vector<size_t> choice;
  std::unordered_set<size_t> picked;
  while (_options.size() && choice.size() < _amount)
  {
    size_t len = _options.size();
    size_t pick  = len;
    std::string owner = "";
    if (_player == PTCG::PLAYER::ENEMY) owner = "enemies ";
    do
    {
        std::cout<<"Pick a card from 0 - "<<len-1<<", to "<<actionStr(_action)<<" from your "<<owner<<_pile<<"?"<<std::endl;
        std::cin>>pick;
    }
    while(!std::cin.fail() && (picked.count(pick) || (pick > (len -1))));
    choice.push_back(pick);
    picked.insert(pick);
  }
  return choice;

 void promptChoice();
{
   return choice;
}


chooseCards(
PLAYER _player,
PILE _origin,
ACTION _action,
:vector<std::unique_ptr<Card>> &_options,
   const unsigned _amount
 )
{
  return promptChoice(_player, pileStr(_origin), _action, _options, _amount);
}

chooseSlot(
PLAYER _owner,
ACTION _action,
vector<BoardSlot> &_options,
const unsigned _amount
    )
{
  return promptChoice(_owner, "bench", _action, _options, _amount);
}

learnCards(
PLAYER _owner,
PILE _origin,
vector<size_t> &_indices,
vector<std::unique_ptr<Card>> &_revealed
    )
{}

std::vector<size_t> HumanPlayer::chooseEnergy(
PLAYER _owner,
PILE _destination,
ACTION _action,
vector<std::unique_ptr<Card> > &_options,
const unsigned _amount
)
{
  return promptChoice(_owner, "active pokemon", _action, _options, _amount);
}

bool HumanPlayer::agree(const PTCG::ACTION _action)
{
  std::string answer;
  do
  {
      std::cout<<"Do you want to "<<actionStr(_action)<<"?[y/n]";
      std::cin>>answer;
      std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
  }
  while(!std::cin.fail() && answer!="y" && answer!="yes" && answer!="n" && answer!="no" );
  return (answer == "y") || (answer == "yes");
}

std::pair<bool, unsigned> HumanPlayer::turn()
{
  // Play cards
  while (agree(PTCG::ACTION::PLAY))
  {
    auto card = chooseCards(PTCG::PLAYER::SELF, PTCG::PILE::HAND, PTCG::ACTION::PLAY, viewHand(), 1);
    if (!card.empty()) playCard(card[0]);
    else std::cout<<"Hand is empty."<<std::endl;
  }

  // Attack?
  bool doAttack = agree(PTCG::ACTION::ATTACK);
  unsigned attack = viewBench().at(0).active()->attackNum();
  if (doAttack)
  {
    unsigned len = attack - 1;
    do
    {
      std::cout<<"Pick an attack from 0 - "<<len<<std::endl;
      std::cin>>attack;
    } while (!std::cin.fail() && attack > len);
  }

  // Return the decision
  return std::pair<bool, unsigned> {doAttack, attack};
}
