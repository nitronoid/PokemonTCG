#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

enum class CMD
{
    RESTART,
    EXIT,
    PLAY,
    ATTACK,
    RETREAT,
    SKIP
};

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
  HumanPlayer(Game& _parentGame) :
    Player(_parentGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~HumanPlayer() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief cloning method
  /// @return a pointer to the player
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the deck name
  /// @return name string
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::string deckName() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing cards
  /// @param [in] _player the owner of the cards
  /// @param [in] _origin the card pile to look in
  /// @param [in] _action a type of action to perform
  /// @param [in] _options ????
  /// @param [in] _amount number of cards to choose
  /// @return vector of cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER _player,
      const PTCG::PILE _origin,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing board slots
  /// @param [in] _player the owner of the slots
  /// @param [in] _action a type of action to perform
  /// @param [in] _options ????
  /// @param [in] _amount number of slots to choose
  /// @return vector of slots
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for revealing the cards
  /// @param [in] _player the owner of the cards
  /// @param [in] _origin the card pile to look in
  /// @param [in] _indices the indices of cards to reveal
  /// @param [io] _revealed the revealed cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual void learnCards(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _origin,
      const std::vector<size_t> &_indices,
      const std::vector<std::unique_ptr<Card>> &_revealed
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing energy cards
  /// @param [in] _owner the owner of the cards
  /// @param [in] _destination the card pile to look in
  /// @param [in] _action a type of action to perform
  /// @param [in] _options ????
  /// @param [in] _amount number of cards to choose
  /// @return vector of energy cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER _owner,
      const PTCG::PILE _destination,
      const PTCG::ACTION _action,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing conditions
  /// @param [in] _owner the owner of the cards
  /// @param [in] _action a type of action to perform
  /// @param [in] _options ????
  /// @param [in] _amount number of conditions to choose
  /// @return vector of conditions
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseConditions(
      const PTCG::PLAYER _owner,
      const PTCG::ACTION _action,
      const std::vector<PTCG::CONDITION> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for choosing cards
  /// @param [in] _action an action to verify
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION _action) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief main method for all player logics sequence
  /// @return a pair of doAttack switch and a card index
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for setting an attack
  /// @param [in] _index an index of the applied attack
  //----------------------------------------------------------------------------------------------------------------------
  void setAttack(const unsigned _index);
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for converting string input into enum
  //----------------------------------------------------------------------------------------------------------------------
  void enumifyInput();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief an id of the attack to perform
  //----------------------------------------------------------------------------------------------------------------------
  unsigned m_attackID;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief switch for performing an attack
  //----------------------------------------------------------------------------------------------------------------------
  bool m_doAttack = false;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief container for command input string
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_inputStr;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief container for converted input command
  //----------------------------------------------------------------------------------------------------------------------
  CMD m_command;

};


#endif // HUMANPLAYER_H
