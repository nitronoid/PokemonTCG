#include "humanplayer.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <unordered_map>

const std::unique_ptr<Command> HumanPlayer::m_commands[] = {
    std::unique_ptr<Command>{new PlayCardCMD},
    std::unique_ptr<Command>{new AttackCMD},
    std::unique_ptr<Command>{new RetreatCMD},
    std::unique_ptr<Command>{new SkipCMD},
    std::unique_ptr<Command>{new RestartCMD},
    std::unique_ptr<Command>{new ExitCMD},
    std::unique_ptr<Command>{new InspectSlotCMD}
  };

Player* HumanPlayer::clone() const
{
  return new HumanPlayer(*this);
}

std::string HumanPlayer::deckName() const
{
  return "test_deck.json";
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
    case act::ATTACK:    { ret = "attack"; break; }
    default: break;
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
    default: break;
  }
  return ret;
}

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
  while (choice.size() < std::min(_options.size(), static_cast<size_t>(_amount)))
  {
    size_t len = _options.size();
    size_t pick  = len;
    std::string owner = "";
    if (_player == PTCG::PLAYER::ENEMY) owner = "enemies ";
    do
    {
      std::cout<<"Pick a card from 1 - "<<len<<", to "<<actionStr(_action)<<" from your "<<owner<<_pile<<std::endl;
      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
      {
        std::cin>>pick;

      }
    }
    while(!std::cin.fail() && (picked.count(pick-1) || (pick > len)));
    --pick;
    choice.push_back(pick);
    picked.insert(pick);
  }
  return choice;
}

std::vector<size_t> HumanPlayer::chooseCards(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  return promptChoice(_owner, pileStr(_origin), _action, _options, _amount);
}

std::vector<size_t> HumanPlayer::chooseSlot(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  return promptChoice(_owner, "bench", _action, _options, _amount);
}

void HumanPlayer::learnCards(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const std::vector<size_t> &_indices,
    const std::vector<std::unique_ptr<Card>> &_revealed
    )
{

}

std::vector<size_t> HumanPlayer::chooseEnergy(
    const PTCG::PLAYER _owner,
    const PTCG::PILE,
    const PTCG::ACTION _action,
    const std::vector<std::unique_ptr<Card> > &_options,
    const unsigned _amount
    )
{
  return promptChoice(_owner, "active pokemon", _action, _options, _amount);
}

std::vector<size_t> HumanPlayer::chooseConditions(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<PTCG::CONDITION> &_options,
    const unsigned _amount
    )
{
  return promptChoice(_owner,"energy cards",_action,_options,_amount);
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

void HumanPlayer::setAttack(const unsigned _index)
{
  m_doAttack = true;
  m_attackID = _index;
}

void HumanPlayer::setTurnEnd()
{
  m_turnFinished = true;
}

HumanPlayer::CMD HumanPlayer::enumifyInput(const std::string &_str)
{
  std::unordered_map<std::string, CMD> enumMap {
    {"exit",    CMD::EXIT},    {"x", CMD::EXIT},
    {"restart", CMD::RESTART}, {"z", CMD::RESTART},
    {"play",    CMD::PLAY},    {"p", CMD::PLAY},
    {"attack",  CMD::ATTACK},  {"a", CMD::ATTACK},
    {"retreat", CMD::RETREAT}, {"r", CMD::RETREAT},
    {"skip",    CMD::SKIP},    {"s", CMD::SKIP},
    {"inspect", CMD::INSPECT}, {"i", CMD::INSPECT},
  };
  if (enumMap.count(_str)) return enumMap[_str];
  else return CMD::SKIP;
}

std::pair<bool, unsigned> HumanPlayer::turn()
{
  m_turnFinished = false;
  m_doAttack = false;
  std::string input;
  while(!m_turnFinished)
  {
    std::cout<<"What do you want to do?"<<std::endl;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin>>input;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    m_commands[enumifyInput(input)]->execute(*this);
  }
  // Return the decision
  return std::pair<bool, unsigned> {m_doAttack, m_attackID-1};
}


