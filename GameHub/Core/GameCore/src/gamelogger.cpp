#include "gamelogger.h"
#include "game.h"
#include <fstream>

GameLogger::GameLogger() : GameObserver()
{
  std::ofstream log;
  log.open(m_logPath, std::ofstream::out | std::ofstream::trunc);
}

void GameLogger::startTurn()
{
  std::string dividor(10,'-');
  std::string body = "Turn " + std::to_string(m_subject->turnCount()) + " start.";
  logToFile(dividor + '\n' + body + '\n' + dividor);
}

void GameLogger::attackUsed(PokemonCard*const _pokemon, const unsigned _index)
{
  std::string msg =
      "Player "
      + currentPlayerStr()
      + " used pokemon ID: "
      + std::to_string(_pokemon->getID())
      + ", name: "
      +  _pokemon->getName()
      + "'s attack "
      + _pokemon->attacks()[_index].name()
      + '.';
  logToFile(msg);
}

void GameLogger::effectUsed(const Ability*const _ability, const PTCG::TRIGGER _trigger)
{
  std::string msg =
      "Ability "
      + _ability->name()
      + ", triggered on "
      + triggerStr(_trigger)
      + " and activated.";
  logToFile(msg);
}

void GameLogger::playCard(const size_t _handIndex, Card*const _card)
{
  std::string msg =
      "Card No."
      + std::to_string(_handIndex)
      + ", name: "
      + _card->getName()
      + ", id: "
      + std::to_string(_card->getID())
      + " in Player "
      + currentPlayerStr()
      + "'s hand has been played.";
  logToFile(msg);
}

void GameLogger::moveCard(
    const PTCG::PLAYER _owner,
    const PTCG::PILE _origin,
    const PTCG::PILE _destination,
    const size_t _index,
    Card * const _card
    )
{
  std::string msg =
      "Card No."
      + std::to_string(_index)
      + ", name: "
      + _card->getName()
      + ", id: "
      + std::to_string(_card->getID())
      + " in Player "
      + playerStr(_owner)
      + "'s "
      + pileStr(_origin)
      + " has been moved to their "
      + pileStr(_destination)
      + '.';
  logToFile(msg);
}

void GameLogger::knockOut(const PTCG::PLAYER _player, const size_t _index)
{
  std::string msg =
      "The pokemon in slot "
      + std::to_string(_index)
      + " on Player "
      + playerStr(_player)
      + "'s bench has been knocked out.";
  logToFile(msg);
}

void GameLogger::swapSlot(const PTCG::PLAYER _player, const size_t _index)
{
  std::string msg =
      "The active slot and slot "
      + std::to_string(_index)
      + " have been swapped on Player "
      + playerStr(_player)
      + "'s bench.";
  logToFile(msg);
}

void GameLogger::inspectSlot(const PTCG::PLAYER _player, const size_t _index)
{
  std::string msg =
      "Player "
      + currentPlayerStr()
      + ", inspected slot "
      + std::to_string(_index)
      + " in player "
      + playerStr(_player)
      + "'s bench.";
  logToFile(msg);
}

void GameLogger::inspectCard(const PTCG::PLAYER _player, const PTCG::PILE _pile, const size_t _index)
{
  std::string msg =
      "Player "
      + currentPlayerStr()
      + ", inspected card "
      + std::to_string(_index)
      + " in player "
      + playerStr(_player)
      + "'s "
      + pileStr(_pile)
      + '.';
  logToFile(msg);
}

std::string GameLogger::playerStr(const PTCG::PLAYER _player)
{
  return std::to_string((m_subject->turnCount() + static_cast<unsigned>(_player)) % 2);
}

std::string GameLogger::currentPlayerStr()
{
  return std::to_string(m_subject->turnCount() % 2);
}

std::string GameLogger::pileStr(const PTCG::PILE _origin)
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

std::string GameLogger::triggerStr(const PTCG::TRIGGER _origin)
{
  using trg = PTCG::TRIGGER;
  std::string ret;
  switch (_origin)
  {
    case trg::NOW:    { ret = "play of card"; break; }
    case trg::START:  { ret = "start of turn"; break; }
    case trg::ATTACK: { ret = "attack"; break; }
    case trg::END:    { ret = "end of turn"; break; }
    default: break;
  }
  return ret;
}

void GameLogger::logToFile(const std::string &_msg)
{
  std::ofstream log;
  log.open(m_logPath, std::ios_base::app);
  log << _msg << '\n';
}
