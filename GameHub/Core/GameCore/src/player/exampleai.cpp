#include "player/exampleai.h"
#include "player/strategyplayer.h"
#include "game.h"
#include <unordered_map>

Player* ExampleAI::clone() const
{
  return new ExampleAI(*this);
}


std::string ExampleAI::deckName() const
{
  return "bright_tide_deck.json";
}

std::vector<size_t> ExampleAI::chooseCards(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const PTCG::ACTION,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  return consecutiveIndices(std::min(_options.size(), static_cast<size_t>(_amount)));
}

std::vector<size_t> ExampleAI::consecutiveIndices(const size_t _length)
{
  std::vector<size_t> first(_length);
  std::iota (std::begin(first), std::end(first), 0);
  return first;
}

size_t ExampleAI::maxRequirement(PokemonCard* const _poke)
{
  size_t max = 0;
  for (const auto& attack : _poke->attacks())
  {
    max = std::max(max, attack.requirements().size());
  }
  return  max;
}

bool ExampleAI::hasEnoughEnergy(const BoardSlot& _slot)
{
  return _slot.active() && _slot.numEnergy() >= maxRequirement(_slot.active());
}

std::vector<size_t> ExampleAI::energyPriority(const size_t _len)
{
  auto bench = viewBench();
  auto indices = consecutiveIndices(bench.size());
  std::sort(indices.begin(), indices.end(), [&bench](const size_t a, const size_t b)
  {
    return bench[a].numEnergy() > bench[b].numEnergy();
  }
  );
  // Find the first card without enough energy
  auto pos = std::find_if(indices.begin(), indices.end(),
                          [&bench, this](const auto& i){ return !hasEnoughEnergy(bench[i]); }
  );
  if (pos == indices.end()) pos = indices.begin();
  std::vector<size_t> ret(pos, pos + std::min(_len, static_cast<size_t>(indices.end() - pos)));
  return ret;
}

size_t ExampleAI::findSlotMostEnergy()
{
  auto bench = viewBench();
  size_t ret = 0;
  size_t energyAmount = 0;
  for (size_t i = 0; i < bench.size(); ++i)
  {
    if (bench[i].numEnergy() > energyAmount)
    {
      energyAmount = bench[i].numEnergy();
      ret = i;
    }
  }
  return ret;
}

std::vector<size_t> ExampleAI::chooseSlot(
    const PTCG::PLAYER _player,
    const PTCG::ACTION _action,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  // My pokemon has been knocked out
  if (!m_myTurn && !_amount && _action == PTCG::ACTION::PLAY)
  {
    return std::vector<size_t>{findSlotMostEnergy()};
  }
  std::vector<size_t> ret;
  switch (m_state)
  {
    case PLAYING_ENERGY :
    {
      ret = energyPriority(_amount);
      break;
    }
    case ATTACKING :
    case HEALING :
    case PLAYING_EVO :
    case PLAYING_TRAINER :
    case PLAYING_BASIC :
    default:
    {
      ret = consecutiveIndices(std::min(_options.size(), static_cast<size_t>(_amount)));
      break;
    }
  }
  return ret;
}

void ExampleAI::learnCards(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const std::vector<size_t> &,
    const std::vector<std::unique_ptr<Card>> &
    )
{}

std::vector<size_t> ExampleAI::chooseEnergy(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const PTCG::ACTION,
    const std::vector<std::unique_ptr<Card> > &_options,
    const unsigned _amount
    )
{
  // view the bench and get the attacks
  auto bench = viewBench();
  auto attacks = bench[0].active()->attacks();
  // Create a set of specific required energy types
  std::unordered_set<PTCG::TYPE> importantRequirements;
  for (const auto& attack : attacks)
  {
    for (const auto& req : attack.requirements())
      importantRequirements.insert(req);
  }
  // Colourless can go because its a wild card
  importantRequirements.erase(PTCG::TYPE::COLOURLESS);

  std::vector<size_t> choice;
  std::unordered_set<size_t> pickedIndices;
  for (size_t i = 0; i < _options.size(); ++i)
  {
    // Access the energy type
    auto energy = static_cast<EnergyCard*>(_options[i].get());
    // add all the non-important energies to our choice
    if (!importantRequirements.count(energy->type()))
    {
      choice.push_back(i);
      // Store this so we don't pick the same one in the next stage
      pickedIndices.insert(i);
    }
  }
  // Now we have no option other than to pick important energies to make up the numbers
  size_t len = std::min(static_cast<size_t>(_amount), _options.size());
  for (size_t i = 0; choice.size() < len; ++i)
  {
    // Don't pick it if we have already
    if (!pickedIndices.count(i))
      choice.push_back(i);
  }
  // Slice the vector down if it was bigger than the amount
  return std::vector<size_t>(choice.begin(), choice.begin() + len);
}

bool ExampleAI::agree(const PTCG::ACTION _action)
{
  static const std::vector<bool> decision = {true, true, false, true, true, true};
  return decision[static_cast<size_t>(_action)];
}

std::vector<size_t> ExampleAI::chooseConditions(
    const PTCG::PLAYER,
    const PTCG::ACTION,
    const std::vector<PTCG::CONDITION> &_options,
    const unsigned _amount
    )
{
  using cnd = PTCG::CONDITION;
  std::unordered_map<cnd, size_t> priorityMap {
    {cnd::ASLEEP, 1},
    {cnd::BURNED, 2},
    {cnd::CONFUSED, 3},
    {cnd::PARALYZED, 4},
    {cnd::POISONED, 5}
  };
  // Create a set of consecutive indices representing the current order of _options
  std::vector<size_t> consecutive(_options.size());
  std::iota (std::begin(consecutive), std::end(consecutive), 0);
  // We then sort the indices using our priority map
  std::sort(consecutive.begin(), consecutive.end(), [&priorityMap, &_options](const size_t a, const size_t b)
  {
    return priorityMap[_options[a]] > priorityMap[_options[b]];
  }
  );
  size_t slicedLen = std::min(static_cast<size_t>(_amount), consecutive.size());
  return std::vector<size_t>(consecutive.begin(), consecutive.begin() + slicedLen);
}


std::unordered_map<PTCG::TYPE, size_t> getMaxRequiredEnergy(const BoardSlot& _slot)
{
  std::unordered_map<PTCG::TYPE, size_t> requirements;
  auto required = _slot.active()->attacks();
  for (const auto& attack : _slot.active()->attacks())
  {
    std::unordered_map<PTCG::TYPE, size_t> required;
    for (const auto& e : attack.requirements())
      ++required[e];
    for (const auto& req : required)
    {
      if (!requirements.count(req.first) || req.second > requirements[req.first])
        requirements[req.first] = req.second;
    }
    requirements.insert(required.begin(), required.end());
  }
  return requirements;
}

std::vector<PTCG::TYPE> getRequiredEnergy(const BoardSlot& _slot)
{
  std::vector<PTCG::TYPE> ret;
  auto required = getMaxRequiredEnergy(_slot);
  auto attached = _slot.energyMSet();
  for (const auto& e : _slot.energyMSet())
  {
    if (required[e])
      required[e]--;
  }
  for (const auto& req : required)
  {
    std::vector<PTCG::TYPE> fromMap(req.second, req.first);
    ret.insert(ret.end(), fromMap.begin(), fromMap.end());
  }
  return ret;
}


void ExampleAI::playEnergy()
{
  auto bench = viewBench();
  auto hand = viewHand();
  auto priorityList = energyPriority(bench.size());
  for (const auto i : priorityList)
  {
    auto slot = bench[i];
    if (!slot.active()) continue;
    auto required = getRequiredEnergy(slot);
    for (const auto& neededEnergy : required)
    {
      auto foundEnergy = std::find_if(hand.begin(), hand.end(), [&neededEnergy](const auto& card)
      {
        if (card->cardType() == PTCG::CARD::ENERGY)
        {
          auto energy = static_cast<EnergyCard*>(card.get());
          return energy->type() == neededEnergy || neededEnergy == PTCG::TYPE::COLOURLESS;
        }
        else
          return  false;
      }
      );
      if (foundEnergy != hand.end())
      {
        m_state = PLAYING_ENERGY;
        playCard(foundEnergy - hand.begin());
        m_state = NONE;
        return;
      }
    }
  }
}

void ExampleAI::playBasic()
{
  auto hand = viewHand();
  for (size_t i = 0; i < hand.size(); ++i)
  {
    if (hand[i]->cardType() == PTCG::CARD::POKEMON)
    {
      auto poke = static_cast<PokemonCard*>(hand[i].get());
      if (!poke->stage() && canPlay(i))
      {
        m_state = PLAYING_BASIC;
        playCard(i);
        m_state = NONE;
        return;
      }
    }
  }
}

void ExampleAI::playEvo()
{
  auto hand = viewHand();
  for (size_t i = 0; i < hand.size(); ++i)
  {
    if (hand[i]->cardType() == PTCG::CARD::POKEMON && canPlay(i))
    {
      m_state = PLAYING_EVO;
      playCard(i);
      m_state = NONE;
      return;
    }
  }
}

int ExampleAI::getDamageSim(const size_t _attackID)
{
  Game dummy = getDummyGame();
  StrategyPlayer dummySelf(&dummy, this);
  StrategyPlayer dummyEnemy(&dummy, this);
  dummy.registerPlayer(&dummySelf, PTCG::PLAYER::SELF);
  dummy.registerPlayer(&dummyEnemy, PTCG::PLAYER::ENEMY);
  dummySelf.setTurn(
      [id=_attackID](Player*_dummyPlayer)
      {
        return std::pair<bool, unsigned> {true, id};
      }
  );
  dummyEnemy.setTurn([](Player*){ return std::pair<bool, unsigned> {false, 0}; });
  // Finally we call next turn, this can be called as many times as you'd like
  dummy.nextTurn();
  // You can then query the current game state by calling the view functions on the dummy game
  auto afterBench = dummySelf.viewBench();
  return afterBench[0].getRemainingHP();
}

unsigned ExampleAI::findBestAttack()
{
  auto bench = viewBench();
  auto enemyBench = viewBench(PTCG::PLAYER::ENEMY);
  auto active = bench[0].active();
  int leastHP = enemyBench[0].getRemainingHP();
  size_t picked = 0;
  for (size_t i = 0; i < active->attackNum(); ++i)
  {
    int testAttack = getDamageSim(i);
    if (testAttack < leastHP)
      picked = i;
  }
  return picked;
}

std::pair<bool, unsigned> ExampleAI::turn()
{
  // use raii to set the turn member variable
  turnRAII raiiturn (&m_myTurn);
  playEnergy();
  playBasic();
  playEvo();

  // Return the decision
  return {true, findBestAttack()};
}


