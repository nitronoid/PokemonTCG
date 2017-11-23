#ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"

class Bench : public CardPile
{
public:
    Bench() = default;
    BoardSlot& cardAt(const unsigned _index);
    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;
private:
    std::array<BoardSlot,5> m_slots;
};

#endif // BENCH_H
