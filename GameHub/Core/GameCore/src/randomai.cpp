#include "randomai.h"
#include "game.h"
#include "playercommand.h"
#include "strategyplayer.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>

Player* RandomAI::clone() const
{
  return new RandomAI(*this);
}


std::string RandomAI::deckName() const
{
  return "test_deck.json";
}

std::vector<size_t> RandomAI::chooseCards(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const PTCG::ACTION,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

std::vector<size_t> RandomAI::chooseSlot(
    const PTCG::PLAYER,
    const PTCG::ACTION,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

void RandomAI::learnCards(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const std::vector<size_t> &,
    const std::vector<std::unique_ptr<Card>> &
    )
{}

std::vector<size_t> RandomAI::chooseEnergy(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const PTCG::ACTION,
    const std::vector<std::unique_ptr<Card> > &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

bool randomBool()
{
  // Random bool generator
  static auto gen = std::bind(
        std::uniform_int_distribution<unsigned>(0u,1u),
        // Use a random_device to seed
        std::default_random_engine(std::random_device{}())
        );
  return gen();
}

bool RandomAI::agree(const PTCG::ACTION)
{
  return randomBool();
}

std::vector<size_t> RandomAI::chooseConditions(
    const PTCG::PLAYER,
    const PTCG::ACTION,
    const std::vector<PTCG::CONDITION> &_options,
    const unsigned _amount
    )
{
  size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

std::pair<bool, unsigned> RandomAI::turn()
{
  Game dummy = getDummyGame();
  StrategyPlayer dummySelf(&dummy, this);
  StrategyPlayer dummyEnemy(&dummy, this);
  dummy.registerPlayer(&dummySelf, 1);
  dummy.registerPlayer(&dummyEnemy, 0);
  dummySelf.setTurn(
        [](Player*_dummyPlayer)
  {
    auto hand = _dummyPlayer->viewHand();
    if (hand.size() && _dummyPlayer->canPlay(0))
      _dummyPlayer->playCard(0);
    return std::pair<bool, unsigned> {false, 0};
  }
        );
  dummyEnemy.setTurn([](Player*){ return std::pair<bool, unsigned> {false, 0}; });
  dummy.nextTurn();
  auto check = dummySelf.viewBench();
  // Random engine
  static std::mt19937_64 eng(std::random_device{}());

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


