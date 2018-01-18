#ifndef TRAINERCARD_H
#define TRAINERCARD_H

#include "card/card.h"

class TrainerCard : public Card
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  TrainerCard(const TrainerCard&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for TrainerCard
  //----------------------------------------------------------------------------------------------------------------------
  TrainerCard(
      const unsigned _id,
      const std::string &_name,
      const Ability &_ability,
      const PTCG::CARD _type
      ) :
    Card(_id, _name, _ability),
    m_type(_type)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~TrainerCard() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clone method
  /// @return a pointer to this object
  //----------------------------------------------------------------------------------------------------------------------
  virtual Card* clone() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief validate card play status
  /// @param [io] parent game
  /// @return true/false
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool canPlay(Game &_game) const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief play current card
  /// @param [io] parent game
  /// @param [in] target index
  //----------------------------------------------------------------------------------------------------------------------
  virtual void playCard(Game&_game, const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get card type
  /// @return card type
  //----------------------------------------------------------------------------------------------------------------------
  virtual PTCG::CARD cardType() const override;
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief card type
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::CARD m_type;

};

#endif // TRAINERCARD_H