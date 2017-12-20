#ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"

class Bench
{
public:
    Bench() = default;
    Bench(const Bench&) = default;
    Bench& operator=(const Bench&) = delete;
    Bench (const std::array<BoardSlot,6>& _slots):
        m_slots(_slots)
    {}

    BoardSlot *slotAt(const unsigned _index);
    PokemonCard *active();
    std::unique_ptr<BoardSlot> view(const unsigned &_index) const;
    void put(std::unique_ptr<Card> &&_card, const unsigned _index);
    std::vector<std::unique_ptr<Card>> take(const unsigned _index);
    unsigned numBenched() const;

private:
    std::array<BoardSlot,6> m_slots;
};

#endif // BENCH_H
