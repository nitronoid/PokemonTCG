#ifndef BLANKCARD_H
#define BLANKCARD_H

#include "card.h"

class BlankCard : public Card
{
public:
  /// @brief default copy ctor
  BlankCard(const BlankCard&) = default;
  /// @brief default assignment operator
  BlankCard& operator=(const BlankCard&) = default;
  /// @brief ctor to construct a blank card, all blank
  BlankCard() : Card(~0, "", Ability{}) {}

  /// @brief canPlay for a blank is empty
  virtual bool canPlay(Game&) const override;
  /// @brief gets a copy of this card
  virtual Card* clone() override;
  /// @brief returns a card type of this card
  virtual PTCG::CARD cardType() const override;

};


#endif // BLANKCARD_H
