#ifndef DECK_H
#define DECK_H
#include <vector>
#include "cardpile.h"
#include <random>

class Deck : public CardPile
{
public:
  /// @brief default ctor
  Deck() = default;
  /// @brief default copy ctor
  Deck (const Deck&_original);
  /// @brief assignment operator
  Deck& operator=(const Deck&);
  /// @brief ctor for constructing a Deck
  /// @param [in] _card cards in this deck
  Deck(std::vector<std::unique_ptr<Card>>&& _cards) :
    m_cards(std::move(_cards))
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~Deck() = default;
  /// @brief initialses the deck such as loading cards
  /// @param [in] _cards cards to be loaded and prepared
  void init(std::vector<std::unique_ptr<Card>> &&_cards);
  /// @brief puts a card into this deck
  /// @param [in] _card card to be put into the deck
  virtual void put(std::unique_ptr<Card> &&_card) override;
  /// @brief takes a card from this deck
  /// @param [in] _index where in the deck the card is
  virtual std::unique_ptr<Card> take(const size_t _index) override;
  /// @brief acesses a card in deck by specifying a deck index
  /// @param [in] _index deck index for the card you're looking for
  virtual Card* cardAt(const size_t _index) override;
  /// @brief takes a card from the top of the deck
  std::unique_ptr<Card> takeTop();
  /// @brief viewing all cards in this deck
  std::vector<std::unique_ptr<Card>> view() const;
  /// @brief check if deck is empty
  inline bool empty() const { return m_cards.empty(); }
  /// @brief shuffles a deck
  void shuffle();
  /// @brief returns the number of cards in this deck
  virtual size_t numCards() const override;
private:
  /// @brief the cards in this deck
  std::vector<std::unique_ptr<Card>> m_cards;

};

#endif // DECK_H
