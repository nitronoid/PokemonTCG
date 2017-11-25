#ifndef DECK_H
#define DECK_H

#include <vector>
#include "cardpile.h"

class Deck : public CardPile
{
public:
    Deck() = default;
    Deck (const Deck&_original);
    Deck& operator=(const Deck&) = delete;

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    const std::vector<std::unique_ptr<Card>>& view();
    void shuffle();
private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // DECK_H
