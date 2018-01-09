#ifndef DECK_H
#define DECK_H
#include <vector>
#include "cardpile.h"
#include <random>

class Deck : public CardPile
{
public:
    Deck() = default;
    Deck (const Deck&_original);
    Deck& operator=(const Deck&);
    Deck(std::vector<std::unique_ptr<Card>>&& _cards) :
      m_cards(std::move(_cards))
    {}


    void init(std::vector<std::unique_ptr<Card>> &&_cards);

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const size_t _index) override;
    virtual Card* cardAt(const size_t _index) override;
    std::unique_ptr<Card> takeTop();
    std::vector<std::unique_ptr<Card>> view() const;
    inline bool empty() const { return m_cards.empty(); }
    void shuffle();
    virtual size_t numCards() const override;
private:
    std::vector<std::unique_ptr<Card>> m_cards;
    
};

#endif // DECK_H
