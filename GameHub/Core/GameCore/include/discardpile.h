#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include "cardpile.h"

class DiscardPile : public CardPile
{
public:
    DiscardPile() = default;
    DiscardPile (const DiscardPile&_original);
    DiscardPile& operator =(const DiscardPile &) = delete;

    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
    const std::vector<std::unique_ptr<Card>>& view();
private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // DISCARDPILE_H
