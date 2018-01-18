#ifndef AIPLAYERBT_H
#define AIPLAYERBT_H

#include "player/player.h"
#include <unordered_map>
#include <algorithm>

class AIPlayerBT : public Player
{
public:

    ///-----------------------------------------------------------------------------------
    /// @build constructor
    ///-----------------------------------------------------------------------------------
    AIPlayerBT(const AIPlayerBT&) = default;
    AIPlayerBT(Game* _parentGame) :
      Player(_parentGame)
    {}
    ///-----------------------------------------------------------------------------------
    /// @build clone
    ///-----------------------------------------------------------------------------------
    virtual Player* clone() const override;
    ///-----------------------------------------------------------------------------------
    /// @build name of deck we are using (Bright Tide)
    ///-----------------------------------------------------------------------------------
    virtual std::string deckName() const override;
    ///-----------------------------------------------------------------------------------
    /// @build chooseCards function
    /// @param _player : which player choose the cards
    /// @param _origin : from which pile are you choosing
    /// @param _action : what do you do with the card
    /// @param _options: pile of cards
    /// @param _amount : how many cards you are choosing
    ///-----------------------------------------------------------------------------------
    virtual std::vector<size_t> chooseCards(
        const PTCG::PLAYER _player,
        const PTCG::PILE _origin,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        ) override;
    ///-----------------------------------------------------------------------------------
    /// @build where to put your cards on the bench/activeCard
    ///-----------------------------------------------------------------------------------
    virtual std::vector<size_t> chooseSlot(
        const PTCG::PLAYER _owner,
        const PTCG::ACTION _action,
        const std::vector<BoardSlot> &_options,
        const unsigned _amount
        ) override;
    ///-----------------------------------------------------------------------------------
    /// @build optional
    ///-----------------------------------------------------------------------------------
    virtual void learnCards(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _origin,
        const std::vector<size_t> &_indices,
        const std::vector<std::unique_ptr<Card>> &_revealed
        ) override;
    ///-----------------------------------------------------------------------------------
    /// @build what do to with the energy, Discard and where to move it
    ///-----------------------------------------------------------------------------------
    virtual std::vector<size_t> chooseEnergy(
        const PTCG::PLAYER _owner,
        const PTCG::PILE _destination,
        const PTCG::ACTION _action,
        const std::vector<std::unique_ptr<Card>> &_options,
        const unsigned _amount
        ) override;
    /// @build chooseConditions
    virtual std::vector<size_t> chooseConditions(
        const PTCG::PLAYER _owner,
        const PTCG::ACTION _action,
        const std::vector<PTCG::CONDITION> &_options,
        const unsigned _amount
        ) override;
    ///-----------------------------------------------------------------------------------
    /// @build function for if you are agreeing with the action or not
    ///-----------------------------------------------------------------------------------
    virtual bool agree(const PTCG::ACTION _action) override;
    ///-----------------------------------------------------------------------------------
    /// @build what do you do while it is your turn
    /// return a pair with bool (attack or not), unsigned (which attack)
    ///-----------------------------------------------------------------------------------
    virtual std::pair<bool, unsigned> turn() override;
    ///-----------------------------------------------------------------------------------
    /// @build plays a basic pokemon on the bench
    ///-----------------------------------------------------------------------------------
    void playBasicPokemonOnBench();
    ///-----------------------------------------------------------------------------------
    /// @build plays an evolution card
    ///-----------------------------------------------------------------------------------
    void playEvolutionCard();
    ///-----------------------------------------------------------------------------------
    /// @build returns a vector that represents the attack with the biggest requirements
    /// @param [_index] : is the index of the attack
    ///-----------------------------------------------------------------------------------
    std::vector<PTCG::TYPE> biggestAttack(int _index);
    ///-----------------------------------------------------------------------------------
    /// @build returns the index of the hand of an energy card
    ///-----------------------------------------------------------------------------------
    int indexHandEnergy();
    ///-----------------------------------------------------------------------------------
    /// @build returns the index of the bench of an energy card
    ///-----------------------------------------------------------------------------------
    int indexBenchEnergy();
    ///-----------------------------------------------------------------------------------
    /// @build attaches an energy card to the pokemon who needs energy
    ///-----------------------------------------------------------------------------------
    void attachEnergy();
    ///-----------------------------------------------------------------------------------
    /// @build plays trainer cards
    ///-----------------------------------------------------------------------------------
    void playTrainerCard();
    ///-----------------------------------------------------------------------------------
    /// @build return which attack we are choosing
    ///-----------------------------------------------------------------------------------
    int whichAttack();
    ///-----------------------------------------------------------------------------------
    /// @build retreats a pokemon
    ///-----------------------------------------------------------------------------------
    void retreatPokemon();
    ///-----------------------------------------------------------------------------------
    /// @build a timer that makes the artificial seem to think
    /// @param [_amountMilliSeconds] : the amount of milliseocnds it "thinks"
    ///-----------------------------------------------------------------------------------
    void setTime(int _amountMilliSeconds);


//    /// @build checks is the card needs energy
//    bool checkIfEnergyNeeded();
//    /// @build checks if the card is an energy card
//    bool checkIfCardIsEnergy();
//    /// @build tree
//    /// @build condition fuction
//    bool checkTwoAttacks();
//    /// @build check if attack one is bigger
//    bool checkAttackBigger();
//    /// @build check vector size of requirement attack
//    bool checkVectorSize(int _i);
//    /// @build check if energy needed
//    bool needEnergy(int _index);
//    void buildTree();
//    /// @build play Energy
//    bool playEnergies(int _index);
//    /// @build check if energy in hand
//    bool energyInHand();

private:

    ///-----------------------------------------------------------------------------------
    /// @build time in milliseconds
    ///-----------------------------------------------------------------------------------
    int m_time = 2000;
    ///-----------------------------------------------------------------------------------
    /// @build
    ///-----------------------------------------------------------------------------------
    Card* m_card = nullptr;
    ///-----------------------------------------------------------------------------------
    /// @build
    ///-----------------------------------------------------------------------------------
    int m_energySlot = 0;

};


#endif // AIPLAYERBT_H
