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

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const size_t _index) override;
    virtual Card* cardAt(const size_t _index) override;
    std::array<std::unique_ptr<Card>,6> view() const;
    virtual size_t numCards() const override;
private:
    std::array<std::unique_ptr<Card>,6> m_cards;
};

#endif // PRIZECARDS_H
