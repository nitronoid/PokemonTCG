#include "simpleprinter.h"
#include "asciicards.h"
#include "game.h"
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

std::string sentinalFromID(const std::string &_str, const std::string &_id)
{
  size_t start = _str.find(_id);
  size_t end = start + _id.size();
  end = _str.find_first_not_of('$', end);
  return  _str.substr(start, end - start);
}

void str_replace(std::string&io_str, const std::string &_rep, std::string _val, const bool _front = true)
{
  size_t pos = io_str.find(_rep);
  size_t len = _rep.size();
  std::string empty(len, ' ');
  if (_val.size() > len) _val = _val.substr(0, len);
  io_str.replace(pos, len, str_pad(_val, len, _front));
}

void str_replace_sent(std::string&io_str, const std::string &_rep, std::string _val, const bool _front = true)
{
  str_replace(io_str, sentinalFromID(io_str, _rep), _val, _front);
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

std::string stringifyChar(char _in, bool _isType=false)
{
  std::string ret;
  if(_isType)
  {
    switch(_in)
    {
      case 'C' :{ret = "COLOURLESS";break;}
      case 'D' :{ret = "DARKNESS";break;}
      case 'N' :{ret = "DRAGON";break;}
      case 'Y' :{ret = "FAIRY";break;}
      case 'F' :{ret = "FIGHTING";break;}
      case 'R' :{ret = "FIRE";break;}
      case 'G' :{ret = "GRASS";break;}
      case 'L' :{ret = "LIGHTNING";break;}
      case 'M' :{ret = "METAL";break;}
      case 'P' :{ret = "PSYCHIC";break;}
      case 'W' :{ret = "WATER";break;}
      default : break;
    }
  }
  else
  {
    switch(_in)
    {
      case 'A' :{ret = "ASLEEP";break;}
      case 'B' :{ret = "BURNED";break;}
      case 'C' :{ret = "CONFUSED";break;}
      case 'R' :{ret = "PARALYZED";break;}
      case 'P' :{ret = "POISONED";break;}
      default : break;
    }
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

std::string SimplePrinter::bigSlotStr(BoardSlot* const _slot, Status *const _activeStatus) const
{
  std::string ret = k_sentinelSlot;
  auto active = _slot->active();
  str_replace_sent(ret, "$ID", std::to_string(active->getID()));
  str_replace_sent(ret, "$RH", std::to_string(_slot->getRemainingHP()));
  str_replace_sent(ret, "$E", std::to_string(_slot->viewEnergy().size()));
  auto tool = _slot->viewTool();
  std::string toolName = "---";
  if (tool) toolName = tool->getName();
  str_replace_sent(ret, "$TOOL", toolName);
  //pokemonStr(ret, active);
  str_replace_sent(ret, "$HP", std::to_string(_slot->active()->hp()));
  str_replace_sent(ret, "$NAME", _slot->active()->getName(), false);
  str_replace_sent(ret, "$T", stringifyChar(charify(_slot->active()->type()),true));

  int i = 0;
  for (const auto& attack : _slot->active()->attacks())
  {
    str_replace_sent(ret, "$A"  + std::to_string(i), attack.name(), false);
    str_replace_sent(ret, "$D"  + std::to_string(i), attack.damageString());
    std::string requirements;
    for (const auto r : attack.requirements()) requirements += charify(r);
    str_replace_sent(ret, "$AR" + std::to_string(i), requirements);
    //ADD ATTACK DESCRIPTION PLACEMENT HERE <--
    ++i;
  }
  for (; i < 2; ++i)
  {
    str_replace_sent(ret, "$A"  + std::to_string(i), "", false);
    str_replace_sent(ret, "$D"  + std::to_string(i), "");
    str_replace_sent(ret, "$AR" + std::to_string(i), "");
  }
  std::string tmpa = std::string{charify(_slot->active()->weakness())};
  str_replace_sent(ret, "$W", tmpa);
  if(tmpa.length()!=0){str_replace_sent(ret, "$WA", "x2");}else{str_replace_sent(ret, "$WA", "");}
  tmpa = std::string{charify(_slot->active()->resistance())};
  str_replace_sent(ret, "$R", tmpa);
  if(tmpa.length()!=0){str_replace_sent(ret, "$RA", "-20");}else{str_replace_sent(ret, "$RA", "");}
  str_replace_sent(ret, "$C", std::to_string(_slot->active()->retreatCost()));
  str_replace_sent(ret, "$ST", std::to_string(_slot->active()->stage()));
  str_replace_sent(ret, "$EVO", _slot->active()->preEvolution());
  int n=_activeStatus->conditions().size();
  i=0;
  for (; i<3; ++i)
  {
    if(n>=i)
    {
      str_replace_sent(ret, "$COND"+std::to_string(i), stringifyChar(charify(_activeStatus->conditions().at(i))));
    }
    else
    {
      str_replace_sent(ret, "$COND"+std::to_string(i), "");
    }
  }
  return ret;
}

std::string SimplePrinter::slotStr(BoardSlot* const _slot) const
{
  std::string ret = k_sentinelSlot;
  auto active = _slot->active();
  if (active)
  {
    str_replace_sent(ret, "$ID", std::to_string(active->getID()));
    str_replace_sent(ret, "$RH", std::to_string(_slot->getRemainingHP()));
    str_replace_sent(ret, "$E", std::to_string(_slot->viewEnergy().size()));
    auto tool = _slot->viewTool();
    std::string toolName = "---";
    if (tool) toolName = tool->getName();
    str_replace_sent(ret, "$TOOL", toolName);
    pokemonStr(ret, active);
  }
  return ret;
}

std::string SimplePrinter::activeStr(BoardSlot* const _activeSlot, Status *const _activeStatus) const
{
  auto ret = slotStr(_activeSlot);
  std::string conditions;
  for (const auto& status : _activeStatus->conditions())
    conditions += charify(status);
  str_replace_sent(ret, "$STATUS", conditions);
  return ret;
}

std::string SimplePrinter::benchStr(Bench * const _bench) const
{
  std::string ret;
  // Produce the bench string
  std::vector<std::string> benchVec(12,"");
  for (unsigned i = 1; i < 6; ++i)
  {
    BoardSlot* slot = _bench->slotAt(i);
    if (slot->active())
      addVec(benchVec, split(slotStr(_bench->slotAt(i))));
    else
      addVec(benchVec, split(k_blankSlot));
  }
  // Concatenate the bench
  for (auto l : benchVec) ret += (l + '\n');
  return ret;
}

void SimplePrinter::pokemonStr(std::string &_str, PokemonCard * const _card) const
{
  str_replace_sent(_str, "$HP", std::to_string(_card->hp()));
  str_replace_sent(_str, "$NAME", _card->getName(), false);
  str_replace_sent(_str, "$T", std::string{charify(_card->type())});

  int i = 0;
  for (const auto& attack : _card->attacks())
  {
    str_replace_sent(_str, "$A"  + std::to_string(i), attack.name(), false);
    str_replace_sent(_str, "$D"  + std::to_string(i), attack.damageString());
    std::string requirements;
    for (const auto r : attack.requirements()) requirements += charify(r);
    str_replace_sent(_str, "$AR" + std::to_string(i), requirements);
    //ADD ATTACK DESCRIPTION PLACEMENT HERE <--
    ++i;
  }
  for (; i < 2; ++i)
  {
    str_replace_sent(_str, "$A"  + std::to_string(i), "", false);
    str_replace_sent(_str, "$D"  + std::to_string(i), "");
    str_replace_sent(_str, "$AR" + std::to_string(i), "");
  }

  str_replace_sent(_str, "$W", std::string{charify(_card->weakness())});
  str_replace_sent(_str, "$R", std::string{charify(_card->resistance())});
  str_replace_sent(_str, "$C", std::to_string(_card->retreatCost()));
}

std::string SimplePrinter::pokemonCardStr(PokemonCard * const _card) const
{
  std::string ret = k_sentinelPokemonCard;
  str_replace_sent(ret, "$TYPE", std::string{stringify(_card->cardType())});
  pokemonStr(ret, _card);
  return ret;
}

std::string SimplePrinter::energyCardStr(EnergyCard * const _card) const
{
  std::string ret;
  switch(_card->type())
  {
    //    case PTCG::TYPE::COLOURLESS : {ret='C'; break;}
    //    case PTCG::TYPE::DARKNESS :   {ret='D'; break;}
    //    case PTCG::TYPE::DRAGON :     {ret='N'; break;}
    //    case PTCG::TYPE::FAIRY :      {ret='Y'; break;}
    //    case PTCG::TYPE::FIGHTING :   {ret='F'; break;}
    case PTCG::TYPE::FIRE :       {ret=k_fireCard; break;}
    case PTCG::TYPE::GRASS :      {ret=k_leafCard; break;}
    case PTCG::TYPE::LIGHTNING :  {ret=k_electricCard; break;}
      //    case PTCG::TYPE::METAL :      {ret='M'; break;}
      //    case PTCG::TYPE::PSYCHIC :    {ret='P'; break;}
    case PTCG::TYPE::WATER :      {ret=k_waterCard; break;}
    default : {ret=k_blankCard; break;}

  }
  return ret;
}

std::string SimplePrinter::trainerCardStr(TrainerCard * const _card, const std::string &_type) const
{
  std::string ret = k_sentinelTrainerCard;
  str_replace_sent(ret, "$TYPE", _type);
  str_replace_sent(ret, "$NAME", _card->getName(), false);
  return ret;
}

std::string SimplePrinter::cardStr(Card * const _card) const
{
  std::string ret;
  using crd = PTCG::CARD;
  switch(_card->cardType())
  {
    case crd::POKEMON : { ret = pokemonCardStr(static_cast<PokemonCard*>(_card)); break; }
    case crd::ENERGY :  { ret = energyCardStr(static_cast<EnergyCard*>(_card)); break; }
    case crd::ITEM :    { ret = trainerCardStr(static_cast<TrainerCard*>(_card), "ITEM"); break; }
    case crd::TOOL :    { ret = trainerCardStr(static_cast<TrainerCard*>(_card), "TOOL"); break; }
    case crd::SUPPORT : { ret = trainerCardStr(static_cast<TrainerCard*>(_card), "SPRT"); break; }
    case crd::STADIUM : { ret = trainerCardStr(static_cast<TrainerCard*>(_card), "STAD"); break; }
    default:  ret = k_blankCard; break;
  }
  return ret;
}

void reline(std::vector<std::string> &io_vec, const size_t _len, const size_t _startLine)
{
  const size_t lines = io_vec.size();
  for (size_t i = _startLine; i < lines; ++i)
  {
    io_vec.push_back(io_vec[i].substr(_len));
    io_vec[i].erase(_len);
  }
}

std::string SimplePrinter::handStr(Hand * const _hand) const
{
  std::string ret;
  auto cards = _hand->view();
  std::vector<std::string> handVec(11,"");
  for (const auto & card : cards)
  {
    addVec(handVec, split(cardStr(card.get())));
  }
  // The max width of the hand is 10 cards
  size_t line = 1, len = (15 * 10);
  // We reline the cards until there are no lines longer than 10
  while ((handVec.end()-1)->size() > len)
  {
    size_t temp = handVec.size();
    reline(handVec, len, line);
    line = temp;
  }
  // Concatenate the hand
  for (auto l : handVec) ret += (l + '\n');
  return ret;
}

std::string SimplePrinter::prizeStr(PrizeCards * const _prize) const
{
  std::string ret;
  std::vector<std::string> prizeVec(4,"");
  for (const auto & card : _prize->view())
  {
    if (card)
      addVec(prizeVec, split(k_prizeCard));
    else
      addVec(prizeVec, split(k_emptyPrize));
  }
  // Concatenate the prize cards
  for (auto l : prizeVec) ret += (l + '\n');
  return ret;
}

void SimplePrinter::drawSide(Board* _board, const bool _isOp)
{
  Bench& bench = _board->m_bench;
  if(_isOp)
  {
    std::cout<<"ACTIVE:\n"<<activeStr(bench.slotAt(0), bench.activeStatus())<<'\n';
    std::cout<<"BENCH:\n"<<benchStr(&bench)<<'\n';
    std::cout<<"HAND:\n"<<handStr(&_board->m_hand);
    std::cout<<"PRIZE:\n"<<prizeStr(&_board->m_prizeCards);
  }
  else
  {
    std::cout<<"PRIZE:\n"<<prizeStr(&_board->m_prizeCards);
    std::cout<<"BENCH:\n"<<benchStr(&bench)<<'\n';
    std::cout<<"ACTIVE:\n"<<activeStr(bench.slotAt(0), bench.activeStatus())<<'\n';
  }
}

void SimplePrinter::inspectSlot(const PTCG::PLAYER _player, const size_t _index)
{
  auto bench = m_subject->getBoard(_player)->m_bench;
  std::cout<<bigSlotStr(bench.slotAt(_index), bench.activeStatus())<<'\n';
}

void SimplePrinter::drawBoard()
{
  drawSide(m_subject->getBoard(PTCG::PLAYER::ENEMY), false);
  drawSide(m_subject->getBoard(PTCG::PLAYER::SELF), true);
}

