#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "playercommand.h"

class HumanPlayer : public Player
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor for HumanPlayer
  //----------------------------------------------------------------------------------------------------------------------
  HumanPlayer(const HumanPlayer&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for HumanPlayer
  /// @param [in] _parentGame the parentgame of the player
  //----------------------------------------------------------------------------------------------------------------------
  HumanPlayer(Game* _subjectGame) :
    Player(_subjectGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~HumanPlayer() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief cloning method
  /// @return a raw pointer to the dynamically allocated player clone
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the deck name
  /// @return name string
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::string deckName() const override;
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
      ) override;
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
      ) override;
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
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing energy cards attached to a pokemon
  /// @param [in] _owner owner of the pokemon
  /// @param [unused] unused param as the human player would know what card they are choosing from
  /// @param [in] _action  the type of action that will be performed on the choice
  /// @param [in] _options cards to choose from
  /// @param [in] _amount amount of cards to choose (if possible)
  /// @return the indices of the picked energy cards, in _options
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;
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
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prompt player to agree to perform action or not
  /// @param [in] _action an action to evaluate
  /// @return the decision, true for agree and false for disagree
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION _action) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for the players turn; decision making, card playing, attacking, retreating, etc...
  /// @return a pair containing a bool for whether you want to attack, and the index of the attack if you do
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method that tells the class what attack to use
  /// @param [in] _index an index of the requested attack
  //----------------------------------------------------------------------------------------------------------------------
  void setAttack(const unsigned _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for ending the turn from a command
  //----------------------------------------------------------------------------------------------------------------------
  void setTurnEnd();

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Enum to be lexed from user input
  //----------------------------------------------------------------------------------------------------------------------
  enum CMD
  {
    PLAY,
    ATTACK,
    RETREAT,
    SKIP,
    RESTART,
    EXIT,
    INSPECT
  };
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for converting string input into enum
  //----------------------------------------------------------------------------------------------------------------------
  CMD enumifyInput(const std::string &_str);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an id of the attack to perform
  //----------------------------------------------------------------------------------------------------------------------
  unsigned m_attackID;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief switch for performing an attack, reset at the start of turn
  //----------------------------------------------------------------------------------------------------------------------
  bool m_doAttack = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief switch for ending the turn, reset at the start of turn
  //----------------------------------------------------------------------------------------------------------------------
  bool m_turnFinished = false;

  static const std::unique_ptr<Command> m_commands[];

};

#endif // HUMANPLAYER_H
