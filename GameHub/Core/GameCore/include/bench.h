#ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"
#include "status.h"

class Bench
{
public:
  /// @brief default ctor
  Bench() = default;
  /// @brief default copy ctor
  Bench(const Bench&) = default;
  /// @brief default assignment operator
  Bench& operator=(const Bench&) = default;
  /// @brief ctor for constructing a Bench
  /// @param _slots index 0 for the active pokemon, 1-5 for the benched pokemon
  Bench (const std::array<BoardSlot,6>& _slots):
    m_slots(_slots)
  {}
  /// @brief retuurning the current status object
  Status *activeStatus();
  /// @brief returns a bench slot of the specified index
  BoardSlot *slotAt(const size_t _index);
  /// @brief returns the current active pokemon on this bench (0th slot)
  PokemonCard *active();
  /// @brief return the entire bench slot as a copy for viewing
  std::array<BoardSlot,6> view() const;
  /// @brief swapping bench slots when switching pokemon
  /// @param [in] _sub the replacement slot for the new active pokemon
  void switchActive(const unsigned &_sub);
  /// @brief puts a card into the bench with a specified bench index
  /// @param [in] _card card to be put into slot
  /// @param [in] _index where the card is to be attached into the bench
  void put(std::unique_ptr<Card> &&_card, const size_t _index);
  /// @brief takes cards from the bench
  /// @param _index index of the card in bench
  std::vector<std::unique_ptr<Card>> take(const size_t _index);
  /// @brief returns the number of occupied bench
  unsigned numBenched() const;

private:
  /// @brief status handler for the active pokemon for this bench
  Status m_activeStatus;
  /// @brief slots in this bench
  std::array<BoardSlot,6> m_slots;
};

#endif // BENCH_H
