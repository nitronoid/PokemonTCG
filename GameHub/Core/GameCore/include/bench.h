#ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"

class Bench : public CardPile
{
public:
    Bench() = default;
    Bench(const Bench&) = default;
    Bench& operator=(const Bench&) = delete;

    BoardSlot& slotAt(const unsigned _index);
    virtual void put(std::unique_ptr<Card> &&_card) override;
    virtual std::unique_ptr<Card> take(const unsigned _index) override;

    unsigned numBenched() const;

private:
    std::array<BoardSlot,5> m_slots;
};

#endif // BENCH_H
