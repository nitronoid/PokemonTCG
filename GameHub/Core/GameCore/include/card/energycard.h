#ifndef ENERGYCARD_H
#define ENERGYCARD_H

#include "card/card.h"

class EnergyCard : public Card
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor for the Card
  //----------------------------------------------------------------------------------------------------------------------
  EnergyCard(const EnergyCard&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the Card
  /// @param [in] _id the id of the card
  /// @param [in] _name the name of the card
  /// @param [in] _ability the ability of the card
  /// @param [in] _amount the amount of energy
  /// @param [in] _type the type of the energy
  //----------------------------------------------------------------------------------------------------------------------
  EnergyCard(const unsigned _id, const std::string &_name, const Ability &_ability, const unsigned _amount, const PTCG::TYPE _type) :
    Card(_id, _name, _ability),
    m_amount(_amount),
    m_type(_type)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~EnergyCard() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief play validation method
  /// @return whether this card can be played
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool canPlay(Game&) const override;

  virtual void playCard(Game&_game, const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method for cloning the card
  /// @return a pointer to the cloned card
  //----------------------------------------------------------------------------------------------------------------------
  virtual Card* clone() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the energy type
  /// @return the pokemon type (fairy/grass/water etc)
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TYPE type() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the amount the energy contained within the card
  /// @return the amount of energy
  //----------------------------------------------------------------------------------------------------------------------
  unsigned amount() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief getter method for retrieving the type of the energy
  /// @return the type of energy
  //----------------------------------------------------------------------------------------------------------------------
  virtual PTCG::CARD cardType() const override;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the amount of energy contained within the card
  //----------------------------------------------------------------------------------------------------------------------
  unsigned m_amount;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the type of the energy
  //----------------------------------------------------------------------------------------------------------------------
  PTCG::TYPE m_type;
};

#endif // ENERGYCARD_H
