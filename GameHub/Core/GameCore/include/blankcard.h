#ifndef BLANKCARD_H
#define BLANKCARD_H

#include "card.h"

class BlankCard : public Card
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  BlankCard(const BlankCard&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  BlankCard& operator=(const BlankCard&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to construct a blank card, all blank, ~0u is the max unsigned int
  //----------------------------------------------------------------------------------------------------------------------
  BlankCard() : Card(~0u, "", Ability{})
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor for Blank Card
  //----------------------------------------------------------------------------------------------------------------------
  ~BlankCard() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief canPlay for a blank is always true
  /// @return whether this card can be played
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool canPlay(Game&) const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief gets a copy of this card
  /// @return copy of this card
  //----------------------------------------------------------------------------------------------------------------------
  virtual Card* clone() override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns PTCG::CARD::BLANK
  /// @return the type of a blank card, mostly blank
  //----------------------------------------------------------------------------------------------------------------------
  virtual PTCG::CARD cardType() const override;

};


#endif // BLANKCARD_H
