#include "aiplayerbt.h"

Player* AIPlayerBT::clone() const
{
    return new AIPlayerBT(*this);
}

std::string AIPlayerBT::deckName() const
{

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
    /// COMMENTS:
    /// situation_0(begin game): player==SELf, _origin == HAND, _action == PLAY, _options[0] (first card: temp), _amount : check if we can play card
    /// situation_1(middle of the game):

}

std::vector<size_t> AIPlayerBT::chooseSlot(const PTCG::PLAYER _owner, const PTCG::ACTION _action, const std::vector<BoardSlot> &_options, const unsigned _amount)
{

}

void AIPlayerBT::learnCards(const PTCG::PLAYER _owner, const PTCG::PILE _origin, const std::vector<size_t> &_indices, const std::vector<std::unique_ptr<Card> > &_revealed)
{

}

std::vector<size_t> AIPlayerBT::chooseEnergy(const PTCG::PLAYER _owner, const PTCG::PILE _destination, const PTCG::ACTION _action, const std::vector<std::unique_ptr<Card> > &_options, const unsigned _amount)
{

}

bool AIPlayerBT::agree(const PTCG::ACTION _action)
{

}

std::pair<bool, unsigned> AIPlayerBT::turn()
{
}

