#ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"
#include "status.h"

class Bench
{
public:
  Bench() = default;
  Bench(const Bench&) = default;
  Bench& operator=(const Bench&) = default;
  Bench (const std::array<BoardSlot,6>& _slots):
    m_slots(_slots)
  {}

  Status *activeStatus();
  BoardSlot *slotAt(const size_t _index);
  PokemonCard *active();
  std::array<BoardSlot,6> view() const;
  void switchActive(const unsigned &_sub);
  void put(std::unique_ptr<Card> &&_card, const size_t _index);
  std::vector<std::unique_ptr<Card>> take(const size_t _index);
  unsigned numBenched() const;

private:
  Status m_activeStatus;
  std::array<BoardSlot,6> m_slots;
};

#endif // BENCH_H
