#ifndef PRIZECARDS_H
#define PRIZECARDS_H

#include <array>
#include "cardpile.h"

class PrizeCards : public CardPile
{
public:
    PrizeCards() = default;
    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    std::unique_ptr<Card> peek(const unsigned _index);
private:
    std::array<std::unique_ptr<Card>,6> m_cards;
};

#endif // PRIZECARDS_H
