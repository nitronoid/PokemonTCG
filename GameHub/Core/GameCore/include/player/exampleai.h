#ifndef EXAMPLEAI_H
#define EXAMPLEAI_H

#include "player/player.h"

class ExampleAI : public Player
{
private:
  enum state { PLAYING_BASIC, PLAYING_EVO, PLAYING_TRAINER, PLAYING_ENERGY, ATTACKING, HEALING, NONE };
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor for Player
  //----------------------------------------------------------------------------------------------------------------------
  ExampleAI(const ExampleAI&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for Player
  /// @param [in] _parentGame the parent game to the player
  //----------------------------------------------------------------------------------------------------------------------
  ExampleAI(Game* _subjectGame) :
    Player(_subjectGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief virtual default dtor for Player
  //----------------------------------------------------------------------------------------------------------------------
  ~ExampleAI() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief object cloning method
  /// @return a raw pointer to the dynamically allocated clone
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the name of the deck
  /// @return the path to the deck
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
      const PTCG::PLAYER _player,
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

private:

  class turnRAII
  {
  public:
    turnRAII(bool*_turn) : raii_turn(_turn)
    {*raii_turn = true;}
    ~turnRAII()
    {*raii_turn = false;}
  private:
    bool* raii_turn;
  };

  size_t findSlotMostEnergy();
  int getDamageSim(const size_t _attackID);
  unsigned findBestAttack();
  void playBasic();
  void playEvo();
  void playEnergy();
  std::vector<size_t> consecutiveIndices(const size_t _length);
  size_t maxRequirement(PokemonCard* const _poke);
  bool hasEnoughEnergy(const BoardSlot& _slot);
  std::vector<size_t> energyPriority(const size_t _len);
  state m_state = NONE;
  bool m_myTurn = false;
};

#endif // EXAMPLEAI_H
