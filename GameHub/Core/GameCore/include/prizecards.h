#ifndef PRIZECARDS_H
#define PRIZECARDS_H

#include <vector>
#include "cardpile.h"

class PrizeCards : public CardPile
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  PrizeCards() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  PrizeCards (const PrizeCards &_original);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy assignment op for CardPile
  //----------------------------------------------------------------------------------------------------------------------
  PrizeCards& operator=(const PrizeCards&);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~PrizeCards() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief put a card inside the PrizeCards pile
  /// @param [in] card to use
  //----------------------------------------------------------------------------------------------------------------------
  virtual void put(std::unique_ptr<Card> &&_card) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief take a card from the PrizeCards pile
  /// @param [in] index of the card to use
  /// @return a pointer to the taken card
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::unique_ptr<Card> take(const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief view card at index
  /// @param [in] index of card to view
  /// @return a pointer to a card to view
  //----------------------------------------------------------------------------------------------------------------------
  virtual Card* cardAt(const size_t _index) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief view the whole PrizeCards pile
  /// @return an array of pointers to cards in the pile
  //----------------------------------------------------------------------------------------------------------------------
  virtual std::vector<std::unique_ptr<Card>> view() const override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get th enumber of cards contained in this pile
  /// @return the number of cards
  //----------------------------------------------------------------------------------------------------------------------
  virtual size_t numCards() const override;
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief all cards contained in this pile
  //----------------------------------------------------------------------------------------------------------------------
  std::array<std::unique_ptr<Card>,6> m_cards;
};

#endif // PRIZECARDS_H
