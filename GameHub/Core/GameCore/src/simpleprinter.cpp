#include "simpleprinter.h"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

std::string str_pad(std::string o_str, const size_t _len, const bool _front = true)
{
  auto it = o_str.begin();
  if (!_front)
    it = o_str.end();
  o_str.insert(it, _len - o_str.size(), ' ');
  return o_str;
}

void str_replace(std::string&io_str, const std::string &_rep, std::string _val,const bool _front = true)
{
  size_t pos = io_str.find(_rep);
  size_t len = _rep.size();
  std::string empty(len, ' ');
  if (_val.size() > len) _val = _val.substr(0, len);
  io_str.replace(pos, len, str_pad(_val, len, _front));
}

char charify(PTCG::TYPE _in)
{
  char ret;
  switch(_in)
  {
    case PTCG::TYPE::COLOURLESS : {ret='C'; break;}
    case PTCG::TYPE::DARKNESS   : {ret='D'; break;}
    case PTCG::TYPE::DRAGON     : {ret='N'; break;}
    case PTCG::TYPE::FAIRY      : {ret='Y'; break;}
    case PTCG::TYPE::FIGHTING   : {ret='F'; break;}
    case PTCG::TYPE::FIRE       : {ret='R'; break;}
    case PTCG::TYPE::GRASS      : {ret='G'; break;}
    case PTCG::TYPE::LIGHTNING  : {ret='L'; break;}
    case PTCG::TYPE::METAL      : {ret='M'; break;}
    case PTCG::TYPE::PSYCHIC    : {ret='P'; break;}
    case PTCG::TYPE::WATER      : {ret='W'; break;}
    default : {ret='-'; break;}
  }
  return ret;
}

char charify(PTCG::CONDITION _in)
{
  char ret;
  switch(_in)
  {
    case PTCG::CONDITION::ASLEEP    : {ret='A'; break;}
    case PTCG::CONDITION::BURNED    : {ret='B'; break;}
    case PTCG::CONDITION::CONFUSED  : {ret='C'; break;}
    case PTCG::CONDITION::PARALYZED : {ret='R'; break;}
    case PTCG::CONDITION::POISONED  : {ret='P'; break;}
    default : {ret='-'; break;}
  }
  return ret;
}

std::string stringify(PTCG::CARD _in)
{
  std::string ret;
  switch(_in)
  {
    case PTCG::CARD::POKEMON    : {ret="POKE"; break;}
    default : {ret="----"; break;}
  }
  return ret;
}

template<typename Out>
void split(const std::string &_str, const char _delim, Out io_result)
{
  std::stringstream ss(_str);
  std::string item;
  while (std::getline(ss, item, _delim))
  {
    *(io_result++) = item;
  }
}

std::vector<std::string> split(const std::string &_str, const char _delim = '\n')
{
  std::vector<std::string> elems;
  split(_str, _delim, std::back_inserter(elems));
  return elems;
}

void addVec(std::vector<std::string> &_lhs, const std::vector<std::string> &_rhs)
{
  assert(_lhs.size() == _rhs.size());
  for (size_t i = 0; i < _lhs.size(); ++i)
  {
    _lhs[i] += _rhs[i];
  }
}

std::string SimplePrinter::slotStr(BoardSlot* const _slot) const
{
  std::string ret = m_sentinelSlot;
  auto active = _slot->active();
  str_replace(ret, "$ID", std::to_string(active->getID()));
  str_replace(ret, "$HP", std::to_string(active->hp()));
  str_replace(ret, "$NAME$$$$$$$$", active->getName(), false);
  str_replace(ret, "$T", std::string{charify(active->type())});
  str_replace(ret, "$E", std::to_string(_slot->viewEnergy().size()));

  auto tool = _slot->viewTool();
  std::string toolName = "---";
  if (tool) toolName = tool->getName();
  str_replace(ret, "$TOOL$$$$$$", toolName);

  int i = 0;
  for (const auto& attack : active->attacks())
  {
    str_replace(ret, "$A"  + std::to_string(i) + "$$$$", attack.name(), false);
    str_replace(ret, "$D"  + std::to_string(i), "---");
    std::string requirements;
    for (const auto r : attack.requirements()) requirements += charify(r);
    str_replace(ret, "$AR" + std::to_string(i), requirements);
    ++i;
  }

  str_replace(ret, "$W", std::string{charify(active->weakness())});
  str_replace(ret, "$R", std::string{charify(active->resistance())});
  str_replace(ret, "$C", std::to_string(active->retreatCost()));
  std::string conditions;
  for (const auto& status : _slot->conditions())
    conditions += charify(status);
  str_replace(ret, "$STATUS$$$$$$$$$", conditions);

  return ret;
}

std::string SimplePrinter::activeStr(BoardSlot* const _activeSlot) const
{
  return slotStr(_activeSlot);
}

std::string SimplePrinter::benchStr(Bench * const _bench) const
{
  std::string ret;
  // Produce the bench string
  std::vector<std::string> benchVec(13,"");
  for (unsigned i = 1; i < 6; ++i)
  {
    BoardSlot* slot = _bench->slotAt(i);
    if (slot->active())
      addVec(benchVec, split(slotStr(_bench->slotAt(i))));
    else
      addVec(benchVec, split(m_blankSlot));
  }
  // Concatenate the bench
  for (auto l : benchVec) ret += (l + '\n');
  return ret;
}

std::string SimplePrinter::pokemonCardStr(PokemonCard * const _card) const
{
  std::string ret = m_sentinelPokemonCard;
  str_replace(ret, "$TYPE", std::string{stringify(_card->cardType())});
  str_replace(ret, "$HP", std::to_string(_card->hp()));
  str_replace(ret, "$NAME$", _card->getName(), false);
  str_replace(ret, "$T", std::string{charify(_card->type())});

  int i = 0;
  for (const auto& attack : _card->attacks())
  {
    str_replace(ret, "$A"  + std::to_string(i) + "$$$$$", attack.name(), false);
    str_replace(ret, "$D"  + std::to_string(i), "---");
    std::string requirements;
    for (const auto r : attack.requirements()) requirements += charify(r);
    str_replace(ret, "$AR" + std::to_string(i), requirements);
    ++i;
  }

  str_replace(ret, "$W", std::string{charify(_card->weakness())});
  str_replace(ret, "$R", std::string{charify(_card->resistance())});
  str_replace(ret, "$C", std::to_string(_card->retreatCost()));
  return ret;
}

std::string SimplePrinter::cardStr(Card * const _card) const
{
  std::string ret;
  using crd = PTCG::CARD;
  switch(_card->cardType())
  {
    case crd::POKEMON : { ret = pokemonCardStr(static_cast<PokemonCard*>(_card)); break;}
    default:  ret = m_blankCard; break;
  }
  return ret;
}

std::string SimplePrinter::handStr(Hand * const _hand) const
{
  std::string ret;
  auto cards = _hand->view();
  std::vector<std::string> handVec(12,"");
  for (const auto & card : cards)
  {
    addVec(handVec, split(cardStr(card.get())));
  }
  // Concatenate the hand
  for (auto l : handVec) ret += (l + '\n');
  return ret;
}

void SimplePrinter::drawBoard(Board* _board, const bool _isOp)
{
  Bench& bench = _board->m_bench;
  std::cout<<"ACTIVE:\n"<<activeStr(bench.slotAt(0))<<'\n';
  std::cout<<"BENCH:\n"<<benchStr(&bench)<<'\n';
  std::cout<<"HAND:\n"<<handStr(&_board->m_hand);
}

