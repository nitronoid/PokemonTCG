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
    Deck& operator=(const Deck&) = default;

    virtual void put(std::unique_ptr<Card> &&_card, const unsigned _index) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    std::vector<std::unique_ptr<Card>> view();
    void shuffle();

private:
    std::vector<std::unique_ptr<Card>> m_cards;
    std::random_device m_seed;
};

#endif // DECK_H
