#include "aiplayerbt.h"

Player* AIPlayerBT::clone() const
{
    return new AIPlayerBT(*this);
}

std::string AIPlayerBT::deckName() const
{
    return "bright_tide_deck.json";
}

std::vector<size_t> AIPlayerBT::chooseCards(const PTCG::PLAYER _player, const PTCG::PILE _origin, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    // vector of indexes
    std::vector<size_t> result;
    // last element of the options
    // length of vector
    size_t sizeOptions = _options.size()-1;
    result.push_back(sizeOptions);
    // return vector of type size_t
    return result;
}

std::vector<size_t> AIPlayerBT::chooseSlot(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<BoardSlot> &_options, const unsigned _amount)
{
    // when to choose a slot,
    // always first slot
    // vector of indexes
    std::vector<size_t> result;
    // last element of the options
    // length of vector
    size_t sizeOptions = _options.size()-1;
    result.push_back(sizeOptions);
    // return vector of type size_t
    return result;
}

void AIPlayerBT::learnCards(const PTCG::PLAYER _owner, const PTCG::PILE _origin, const std::vector<size_t> &_indices, const std::vector<std::unique_ptr<Card> > &_revealed)
{
    /// OPTIONAL
}

std::vector<size_t> AIPlayerBT::chooseEnergy(const PTCG::PLAYER _owner, const PTCG::PILE _destination, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{
    // when to choose energy
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
    // what to do if it is your turn you have different possibilities
    // put basic pokemon onto bench
    // evolve pokemon
    // attatch an energy card from your hand to one of your pokemon
    // iterate through positions
    auto currentHand = viewHand();
    for(auto& card : viewHand())
    {
        for(unsigned index = 0; index < currentHand.size(); ++index)
        {
            if(card->cardType() == PTCG::CARD::ENERGY)
            {
                if(canPlay(index))
                    playCard(index);
            }
        }
        //std::cout<<" "<<card->getName()<<'\n';
    }

    // play trainer cards
    // retreat your Active Pokemon
    // use abilities
    // attacks

    // attach energy
    std::cout<<"AI PLAY"<<'\n';
    return std::pair<bool, unsigned> {true, 0};

    /// Game.h playCard function help and check the other funtions
}

