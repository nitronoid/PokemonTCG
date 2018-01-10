#ifndef AIPLAYERBT_H
#define AIPLAYERBT_H

/// BrightTide includes
#include "sequence.h"
#include "selector.h"
#include "action.h"
#include "condition.h"
#include "player.h"

class AIPlayerBT : public Player
{
public:
    AIPlayerBT(const AIPlayerBT&) = default;
    AIPlayerBT(Game& _parentGame) :
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
  ///-----------------------------------------------------------------------------------
  /// @build function for if you are agreeing with the action or not
  ///-----------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION _action) override;
  ///-----------------------------------------------------------------------------------
  /// @build what do you do while it is your turn
  /// return a pair with bool (attack or not), unsigned (which attack)
  ///-----------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() override;

};

#endif // AIPLAYERBT_H
