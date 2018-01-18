#ifndef AIPLAYERBT_H
#define AIPLAYERBT_H

/// BrightTide includes
#include "sequence.h"
#include "selector.h"
#include "action.h"
#include "condition.h"
#include "player.h"
#include <unordered_map>
#include <algorithm>


/// TODO
/// when to put a pokemon onto the bench, and which pokemon
/// when to play trainer cards?
/// when to retreat active card?
/// when to use abilities?
/// when to attack?
/// when to evolve a pokemon?
///
/// need a function that returns an int for the enemy attack
/// need a function that returns if attack is an int (not a x,+ or empty)

class AIPlayerBT : public Player
{
public:
    AIPlayerBT(const AIPlayerBT&) = default;
    AIPlayerBT(Game* _parentGame) :
      Player(_parentGame)
    {}

  virtual Player* clone() const override;

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
  /// NOTE: checks if the vector is full, if not choose index that is not full
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
  ///
  /// return a pair with bool (attack or not), unsigned (which attack)
  ///-----------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() override;


    /// @build put pokemon on bench
    void putBasicPokemonOnBench();
    /// @build play the evolution pokemon card (pokemon evolve to the next stage)
    void playEvolutionCard();
    /// @build attach an energy
    void attachEnergy();
    /// @build timer (think)
    void setTime(int _amountMilliSeconds);


    /// @build sort energies of biggest attack
    std::vector<PTCG::TYPE> sortEnergies();
    /// @build return the biggest attack
    std::vector<PTCG::TYPE> biggestAttack(int _index);
    /// @build when to retreat
    void willRetreat();
    /// @build play TRAINER cards
    void playTrainerCard();

    /// @build checks is the card needs energy
    bool checkIfEnergyNeeded();
    /// @build checks if the card is an energy card
    bool checkIfCardIsEnergy();
    /// @build tree
    /// @build condition fuction
    bool checkTwoAttacks();
    /// @build check if attack one is bigger
    bool checkAttackBigger();
    /// @build check vector size of requirement attack
    bool checkVectorSize(int _i);
    /// @build check if energy needed
    bool needEnergy(int _index);
    void buildTree();
    /// @build play Energy
    bool playEnergies(int _index);
    /// @build check if energy in hand
    bool energyInHand();

private:
    /// @build this decides if you attack or not
    bool m_attack = false;
    /// @build this decides which attack you are choosing first(0) or second(1)
    int m_chooseAttack = 0;
    /// @build time in milliseconds
    int m_time = 1000;
};


#endif // AIPLAYERBT_H
