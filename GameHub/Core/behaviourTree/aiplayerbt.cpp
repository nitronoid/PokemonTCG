#include "aiplayerbt.h"
#include <chrono>
#include <thread>

Player* AIPlayerBT::clone() const
{
    return new AIPlayerBT(*this);
}

std::string AIPlayerBT::deckName() const
{
    return "test_deck.json";
}

std::vector<size_t> AIPlayerBT::chooseCards(const PTCG::PLAYER _player, const PTCG::PILE _origin, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::vector<size_t> AIPlayerBT::chooseSlot(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<BoardSlot> &_options, const unsigned _amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

void AIPlayerBT::learnCards(const PTCG::PLAYER _owner, const PTCG::PILE _origin, const std::vector<size_t> &_indices, const std::vector<std::unique_ptr<Card> > &_revealed)
{
    /// OPTIONAL
}

std::vector<size_t> AIPlayerBT::chooseEnergy(const PTCG::PLAYER _owner, const PTCG::PILE _destination, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
}

std::vector<size_t> AIPlayerBT::chooseConditions(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<PTCG::CONDITION> &_options, const unsigned _amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    size_t length = std::min(static_cast<unsigned>(_options.size()), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;

}

bool AIPlayerBT::agree(const PTCG::ACTION _action)
{
    // when do we agree to an action
    // different type of actions are
    // DRAW DISCARD PLAY VIEW MOVE HEAL ATTACK
    return true;
}

std::pair<bool, unsigned> AIPlayerBT::turn()
{
    // variables
    m_attack = false;;
    // what to do if it is your turn you have different possibilities:
    // put basic pokemon onto bench x
//    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//    putPokemonOnBench();
    // you can only play one energy at a time
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    playEnergy();

    // evolve pokemon
    // required energies for attack 1
    // the number energy attached on card
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    if(viewBench()[0].active()->attacks()[1].requirements().size() <= viewBench()[0].numEnergy())
    {
        m_attack = true;
    }

    // play trainer cards
    // retreat your Active Pokemon
    // use abilities

    // check if there is energy attached to the card
    // if energy is attatched to the card, only attack if enough energy
    // else dont attack(return false)
    // attacks
    return std::pair<bool, unsigned> {m_attack, 0};

    /// Game.h playCard function help and check the other funtions
}


void AIPlayerBT::playEnergy()
{
    for(unsigned int i=0; i<viewHand().size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(viewHand()[i]->cardType() == PTCG::CARD::ENERGY)
        {   // make a card energy from your hand
            EnergyCard* typeOfEnergyHand = static_cast<EnergyCard*>(viewHand()[i].get());
            // if that card energy == requirements
            if(typeOfEnergyHand->type() == typeReturnofActiveCard()
                    // this is wrong
                    || typeReturnofActiveCard() == PTCG::TYPE::COLOURLESS)
            {
                if(canPlay(i))
                    playCard(i);
            }

        }
    }
}

void AIPlayerBT::putPokemonOnBench()
{
    for(unsigned int i=0; i<viewHand().size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(viewHand()[i]->cardType() == PTCG::CARD::POKEMON)
            //EnergyCard* pokemon = static_cast<EnergyCard*>(viewHand()[i].get());
            if(canPlay(i))
                playCard(i);
    }
}

bool AIPlayerBT::checkTrainerinHand()
{
    for(unsigned int i = 0; i<viewHand().size(); ++i)
    {
        if(viewHand()[i]->cardType() == PTCG::CARD::ITEM
                || viewHand()[i]->cardType() == PTCG::CARD::SUPPORT
                || viewHand()[i]->cardType() == PTCG::CARD::STADIUM)
        {
            return true;
        }
        return false;
    }
}

PTCG::TYPE AIPlayerBT::typeReturnofActiveCard()
{
    // goes through the requirement energies in attack 1
    for(int i = 0; i < viewBench()[0].active()->attacks()[0].requirements().size(); ++i)
    {
        // return the energy needed for attack one
        return viewBench()[0].active()->attacks()[0].requirements()[0];
    }
}

bool AIPlayerBT::testTree()
{
    for(unsigned int i=0; i<viewHand().size(); ++i)
    {
        // checks if the card in your hand is an energy card
        if(viewHand()[i]->cardType() == PTCG::CARD::ENERGY)
        {
            return true;
        }
        return false;
    }
}
