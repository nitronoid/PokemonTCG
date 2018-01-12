#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include "cardpile.h"

class DiscardPile : public CardPile
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  DiscardPile() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor required for cloning all cards
  //----------------------------------------------------------------------------------------------------------------------
  DiscardPile (const DiscardPile&_original);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy asignment operator required for cloning all cards
  //----------------------------------------------------------------------------------------------------------------------
  DiscardPile& operator =(const DiscardPile &);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to put cards into the discard pile
  /// @param [in] _card card to insert
  //----------------------------------------------------------------------------------------------------------------------
  virtual void put(std::unique_ptr<Card> &&_card) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to take cards from discard pile
  /// @param [in] _index index of the card, in discard pile, to be taken.
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::unique_ptr<Card> take(const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method returns a reference pointer to a card in a specific position of the pile
  /// @param [in] _index index of the card, in discard pile, to be returned.
  //----------------------------------------------------------------------------------------------------------------------
  virtual Card* cardAt(const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief viewing all cards in discard pile
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> view() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the number of cards in discard pile
  //----------------------------------------------------------------------------------------------------------------------
  virtual size_t numCards() const override;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief cards in this pile
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // DISCARDPILE_H
