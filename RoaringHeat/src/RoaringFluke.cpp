#include "RoaringFluke.h"
#include "playercommand.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>

Player* RoaringFluke::clone() const
{
    return new RoaringFluke(*this);
}


std::string RoaringFluke::deckName() const
{
    return "test_deck.json";
}

std::vector<size_t> RoaringFluke::chooseCards(
        const PTCG::PLAYER _player,
        const PTCG::PILE _origin,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        )
{
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::vector<size_t> RoaringFluke::chooseSlot(
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

void RoaringFluke::learnCards(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _origin,
        const std::vector<size_t> &_indices,
        const std::vector<std::unique_ptr<Card>> &_revealed
        )
{}

std::vector<size_t> RoaringFluke::chooseEnergy(
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

bool randomishBool()
{
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    return gen();
}

bool RoaringFluke::agree(const PTCG::ACTION _action)
{
    return randomishBool();
}

std::vector<size_t> RoaringFluke::chooseConditions(
    const PTCG::PLAYER _owner,
    const PTCG::ACTION _action,
    const std::vector<PTCG::CONDITION> &_options,
    const unsigned _amount
    )
{
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::pair<bool, unsigned> RoaringFluke::turn()
{
    // Random engine
    static std::random_device seed;
    static std::mt19937_64 eng(seed());

    // Play random card from hand
    std::uniform_int_distribution<unsigned> hgen(0, static_cast<unsigned>(viewHand().size() - 1));
    playCard(hgen(eng));

    // Should we attack?
    bool doAttack = randomishBool();

    // Play random card from hand
    unsigned attackNum = viewBench().at(0).active()->attackNum();
    std::uniform_int_distribution<unsigned> agen(0, attackNum - 1);

    // Return the decision
    return std::pair<bool, unsigned> {doAttack, agen(eng)};
}


