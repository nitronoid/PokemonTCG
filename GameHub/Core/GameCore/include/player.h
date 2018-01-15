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
  /// @brief default copy ctor for Player
  //----------------------------------------------------------------------------------------------------------------------
  Player(const Player&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for Player
  /// @param [in] _parentGame the parent game to the player
  //----------------------------------------------------------------------------------------------------------------------
  Player(Game* _subjectGame) :
    m_subjectGame(_subjectGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief virtual default dtor for Player
  //----------------------------------------------------------------------------------------------------------------------
  virtual ~Player();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief object cloning method
  /// @return a raw pointer to the dynamically allocated clone
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the name of the deck
  /// @return the path to the deck
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::string deckName() const = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief card choice method
  /// @param [in] _owner owner of the card pile
  /// @param [in] _origin the card pile where the options currently are
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
  /// @return the indices of the picked cards, in _options
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief slot choice method
  /// @param [in] _owner owner of the slots
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options slots to choose from
  /// @param [in] _amount amount of slots to choose (if possible)
  /// @return the indices of the picked slots, in _options
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to reveal cards to the player
  /// @param [in] _owner owner of the card pile
  /// @param [in] _origin the card pile where the cards currently are
  /// @param [in] _indices the locations of the revealed cards in _origin
  /// @param [in] _revealed the revealed cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing energy cards attached to a pokemon
  /// @param [in] _owner owner of the pokemon
  /// @param [in] _destination  the card pile where the energy will be moved to
  /// @param [in] _action  the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
  /// @return the indices of the picked energy cards, in _options
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing a condition that the active pokemon is suffering from
  /// @param [in] _owner owner of the pokemon
  /// @param [in] _action the type of action that will be performed on the choice
  /// @param [in] _options conditions to choose from
  /// @param [in] _amount amount of conditions to choose
  /// @return the indices of the picked conditions, in _options
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseConditions(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> &_options,
      const unsigned _amount
      ) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prompt player to agree to perform action or not
  /// @param [in] _action an action to evaluate
  /// @return the decision, true for agree and false for disagree
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION _action) = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for the players turn; decision making, card playing, attacking, retreating, etc...
  /// @return a pair containing a bool for whether you want to attack, and the index of the attack if you do
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() = 0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for checking if a card can be played
  /// @param [in] _index index of the card to check
  //----------------------------------------------------------------------------------------------------------------------
  bool canPlay(const size_t &_index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for playing a card
  /// @param [in] _index index of the card in hand to play
  //----------------------------------------------------------------------------------------------------------------------
  void playCard(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for inspecting a board slot
  /// @param [in] _owner owner of the slot to inspect
  /// @param [in] _index index of the slot to inspect
  //----------------------------------------------------------------------------------------------------------------------
  void inspectSlot(const PTCG::PLAYER _owner, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for retreating
  //----------------------------------------------------------------------------------------------------------------------
  void retreat();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for viewing a copy of the hand
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> viewHand() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for viewing the number of cards in a pile
  //----------------------------------------------------------------------------------------------------------------------
  size_t numCards(const PTCG::PLAYER _owner, const PTCG::PILE _pile) const;
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
  /// @brief method for retrieving a clone of game to run turn simulations on
  //----------------------------------------------------------------------------------------------------------------------
  Game getDummyGame() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method that attaches this player to a new game, by setting the member pointer
  //----------------------------------------------------------------------------------------------------------------------
  void attachToGame(Game*const _newSubject);

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the game this player is currently participating in.
  //----------------------------------------------------------------------------------------------------------------------
  Game* m_subjectGame;
};

#endif // PLAYER_H
