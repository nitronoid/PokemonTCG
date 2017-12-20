#ifndef PRIZECARDS_H
#define PRIZECARDS_H

#include <vector>
#include "cardpile.h"

class PrizeCards : public CardPile
{
public:
    PrizeCards() = default;
    PrizeCards (const PrizeCards &_original);
    PrizeCards& operator=(const PrizeCards&) = delete;

    virtual void put(std::unique_ptr<Card> &&) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    std::vector<std::unique_ptr<Card>> view() const;

private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // PRIZECARDS_H
