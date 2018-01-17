#include "player/randomai.h"
#include "game.h"
#include "player/playercommand.h"
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
  return "roaring_heat_deck.json";
}

template<typename T>
std::vector<size_t> pickFirst(const std::vector<T> &_options, const size_t _amount)
{
  size_t length = std::min(_options.size(), _amount);
  std::vector<size_t> badChoice(length);
  std::iota (std::begin(badChoice), std::end(badChoice), 0);
  return badChoice;
}

std::vector<size_t> RandomAI::chooseCards(
    const PTCG::PLAYER,
    const PTCG::PILE,
    const PTCG::ACTION,
    const std::vector<std::unique_ptr<Card>> &_options,
    const unsigned _amount
    )
{
  return pickFirst(_options, _amount);
}

std::vector<size_t> RandomAI::chooseSlot(
    const PTCG::PLAYER,
    const PTCG::ACTION,
    const std::vector<BoardSlot> &_options,
    const unsigned _amount
    )
{
  return pickFirst(_options, _amount);
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
  return pickFirst(_options, _amount);
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
  return pickFirst(_options, _amount);
}

std::pair<bool, unsigned> RandomAI::turn()
{
  // Random engine
  static std::mt19937_64 eng(std::random_device{}());

  // Play random card from hand
  std::uniform_int_distribution<unsigned> hgen(0, static_cast<unsigned>(viewHand().size() - 1));
  playCard(hgen(eng));

  // Should we attack?
  bool doAttack = randomBool();

  // Play random card from hand
  unsigned attackNum = viewBench()[0].active()->attackNum();
  std::uniform_int_distribution<unsigned> agen(0, attackNum - 1);

  // Return the decision
  return std::pair<bool, unsigned> {doAttack, agen(eng)};
}


