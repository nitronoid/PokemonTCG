#ifndef CARDPILE_H
#define CARDPILE_H

#include "card.h"
#include <memory>

class CardPile
{
public:
    virtual ~CardPile(){}
    virtual void put(std::unique_ptr<Card> &&_card)=0;
    virtual std::unique_ptr<Card> take(const size_t _index)=0;
};

#endif // CARDPILE_H
