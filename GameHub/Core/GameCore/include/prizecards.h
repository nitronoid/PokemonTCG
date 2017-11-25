#ifndef PRIZECARDS_H
#define PRIZECARDS_H

#include <array>
#include "cardpile.h"

class PrizeCards : public CardPile
{
public:
    PrizeCards() = default;
    PrizeCards (const PrizeCards &_original);
    PrizeCards& operator=(const PrizeCards&) = delete;

    virtual void put(std::unique_ptr<Card> &&) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    const std::array<std::unique_ptr<Card>, 6> &view();

private:
    std::array<std::unique_ptr<Card>, 6> m_cards;
};

#endif // PRIZECARDS_H
