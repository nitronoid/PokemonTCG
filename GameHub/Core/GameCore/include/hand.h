#ifndef HAND_H
#define HAND_H

#include "cardpile.h"
#include <vector>

class Hand : public CardPile
{
public:
    Hand() = default;
    Hand (const Hand &_original);
    Hand& operator=(const Hand &) = delete;

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    std::vector<std::unique_ptr<Card>> view();
private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // HAND_H
