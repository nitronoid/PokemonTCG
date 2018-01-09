#ifndef BRIGHTTIDEAIPLAYER_H
#define BRIGHTTIDEAIPLAYER_H

#include "player.h"

class BrightTideAIPlayer : public Player
{
public:
    /// @build constructor
    BrightTideAIPlayer(const BrightTideAIPlayer&) = default;
    BrightTideAIPlayer(Game& _parentGame) :
      Player(_parentGame)
    {}

    /// @build ?
    virtual Player* clone() const override;

    /// @build chooseCards function to implement
    virtual std::vector<size_t> chooseCards(
        const PTCG::PLAYER _player,
        const PTCG::PILE _origin,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        ) override;
    /// @build chooseSlot function
    virtual std::vector<size_t> chooseSlot(
        const PTCG::PLAYER _owner,
        const PTCG::ACTION _action,
        const std::vector<BoardSlot> &_options,
        const unsigned _amount
        ) override;

    /// @build learnCards function
    virtual void learnCards(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _origin,
        const std::vector<size_t> &_indices,
        const std::vector<std::unique_ptr<Card>> &_revealed
        ) override;
    /// @build chooseEnergy function
    virtual std::vector<size_t> chooseEnergy(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _destination,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        ) override;
    /// @build
    virtual bool agree(const PTCG::ACTION _action) override;
    /// @build (behaviour tree, it is your turn to think)
    virtual std::pair<bool, unsigned> turn() override;

};

#endif // BRIGHTTIDEAIPLAYER_H
