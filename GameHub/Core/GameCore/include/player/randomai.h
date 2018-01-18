#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "player/player.h"

class RandomAI : public Player
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  RandomAI(const RandomAI&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for RandomAI
  //----------------------------------------------------------------------------------------------------------------------
  RandomAI(Game* _subjectGame) :
    Player(_subjectGame)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~RandomAI() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief cnone the pointer to this object
  /// @return a pointer to the player
  //----------------------------------------------------------------------------------------------------------------------
  virtual Player* clone() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the deck name
  /// @return string name
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::string deckName() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief choose cards from a pile
  /// @param [in] the owner of the card pile
  /// @param [in] the type of pile to look at
  /// @param [in] the type of action to perform
  /// @param [in] the cards to choose from
  /// @param [in] the amount of cards to choose
  /// @return a vector of pointers to cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseCards(
      const PTCG::PLAYER,
      const PTCG::PILE,
      const PTCG::ACTION,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief choose slots
  /// @param [in] the owner of the slots
  /// @param [in] the type of action to perform
  /// @param [in] the slots to choose from
  /// @param [in] the amount of slots to choose
  /// @return a vector of pointers to slots
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseSlot(
      const PTCG::PLAYER,
      const PTCG::ACTION,
      const std::vector<BoardSlot> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief reveal cards to player
  /// @param [in] the owner of the cards
  /// @param [in] the card pile to look at
  /// @param [in] the indices of the cards to reveal
  /// @param [in] the cards to choose from
  //----------------------------------------------------------------------------------------------------------------------
  virtual void learnCards(
      const PTCG::PLAYER,
      const PTCG::PILE,
      const std::vector<size_t> &,
      const std::vector<std::unique_ptr<Card>> &
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief choose energy cards
  /// @param [in] the owner of the slots
  /// @param [in] the card pile to look at
  /// @param [in] the type of action to perform
  /// @param [in] the cards to choose from
  /// @param [in] the amount of cards to choose
  /// @return a vector of pointers to cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseEnergy(
      const PTCG::PLAYER,
      const PTCG::PILE,
      const PTCG::ACTION,
      const std::vector<std::unique_ptr<Card>> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief choose conditions
  /// @param [in] the owner of the conditions
  /// @param [in] the type of action to perform
  /// @param [in] the conditions to choose from
  /// @param [in] the amount of conditions to choose
  /// @return a vector of conditions
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<size_t> chooseConditions(
      const PTCG::PLAYER,
      const PTCG::ACTION,
      const std::vector<PTCG::CONDITION> &_options,
      const unsigned _amount
      ) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief validate action
  /// @param [in] the type of action to validate
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool agree(const PTCG::ACTION) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for the players turn; decision making, card playing, attacking, retreating, etc...
  /// @return a pair of a bool(attack or not) and a card id
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::pair<bool, unsigned> turn() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief generates a random bool value
  /// @return a random bool
  //----------------------------------------------------------------------------------------------------------------------
  bool randomBool();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief picks the first options
  /// @param _options is a vector of some type of options
  /// @param _amount is the amount of options to pick
  /// @return the indices to the first options
  //----------------------------------------------------------------------------------------------------------------------
  template<typename T>
  std::vector<size_t> pickFirst(const std::vector<T> &_options, const size_t _amount)
  {
    size_t length = std::min(_options.size(), _amount);
    std::vector<size_t> badChoice(length);
    std::iota (std::begin(badChoice), std::end(badChoice), 0);
    return badChoice;
  }
};


#endif // RANDOMAI_H
