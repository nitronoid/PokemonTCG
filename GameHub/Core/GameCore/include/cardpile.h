#ifndef CARDPILE_H
#define CARDPILE_H

#include "card.h"
#include <memory>

class CardPile
{
public:
  /// @brief virtual dtor for a cardPile
  virtual ~CardPile(){}
  /// @brief puting a card into a pile
  /// @param [in] _card card to put into pile
  virtual void put(std::unique_ptr<Card> &&_card)=0;
  /// @brief taking a card from a pile
  /// @param [in] _index card index to take from pile
  virtual std::unique_ptr<Card> take(const size_t _index)=0;
  /// @brief returning a card info from a requested card index
  /// @param [in] _index requested card index to access
  virtual Card* cardAt(const size_t _index) = 0;
  /// @brief returning the number of cards in a pile
  virtual size_t numCards() const = 0;
};

#endif // CARDPILE_H
