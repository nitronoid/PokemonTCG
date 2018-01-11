#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "board.h"
#include <vector>
#include <memory>
#include <tuple>

class Player
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor for Player
  //----------------------------------------------------------------------------------------------------------------------
  Player(const Player&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for Player
  /// @param [in] _parentGame the parent game to the player
  //----------------------------------------------------------------------------------------------------------------------
  Player(Game& _parentGame) :
    m_parentGame(_parentGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for Player
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Player();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief class cloning method
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the name of the deck
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::string deckName() const = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief card getter method
  /// @param [in] _player owner of the card pile
  /// @param [in] _origin type of the card pile
  /// @param [in] _action a type of action to perform
  /// @param [in] _options cards to use
  /// @param [in] _amount amount of cards to use
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief slot getter method
  /// @param [in] _owner owner of the card pile
  /// @param [in] _action a type of action to perform
  /// @param [in] _options target slot vector to use
  /// @param [in] _amount amount of cards to use
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to reveal cards
  /// @param [in] _owner owner of the card pile
  /// @param [in] _origin type of the card pile
  /// @param [in] _indices indices of cards to use
  /// @param [in] _revealed a vector of revealed cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving energy cards
  /// @param [in] _owner owner of the card pile
  /// @param [in] _destination type of the card pile
  /// @param [in] _action a type of action to perform
  /// @param [in] _options cards to use
  /// @param [in] _amount amount of cards to use
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prompt player to agree to perform action or not
  /// @param [in] _action an action to evaluate
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION _action) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief main player method for deduction, evaluation and decision making
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for validating card
  /// @param [in] _index index of the card to evaluate
  //----------------------------------------------------------------------------------------------------------------------
  bool canPlay(const size_t &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for playing a card
  /// @param [in] _index index of the card to play
  //----------------------------------------------------------------------------------------------------------------------
  void playCard(const size_t &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for retreating
  //----------------------------------------------------------------------------------------------------------------------
  void retreat();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for viewing the hand
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> viewHand() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for viewing the discard pile
  /// @param [in] _owner the owner of the discard pile, defaults to self
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> viewDiscard(const PTCG::PLAYER &_owner = PTCG::PLAYER::SELF) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for viewing the bench sots
  /// @param [in] _owner the owner of the discard pile, defaults to self
  //----------------------------------------------------------------------------------------------------------------------
  std::array<BoardSlot, 6> viewBench(const PTCG::PLAYER &_owner = PTCG::PLAYER::SELF) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for retrieving a copy of game
  //----------------------------------------------------------------------------------------------------------------------
  Game getDummyGame() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for checking whether a player can retreat
  //----------------------------------------------------------------------------------------------------------------------
  bool canRetreat() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for setting the retreat option
  //----------------------------------------------------------------------------------------------------------------------
  void setRetreat(const bool _val);
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief retreat status container
  //----------------------------------------------------------------------------------------------------------------------
  bool m_canRetreat = true;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parent game of this player
  //----------------------------------------------------------------------------------------------------------------------
  Game& m_parentGame;
};

#endif // PLAYER_H
