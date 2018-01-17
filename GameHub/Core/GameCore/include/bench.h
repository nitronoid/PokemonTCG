 #ifndef BENCH_H
#define BENCH_H

#include "boardslot.h"
#include "cardpile.h"
#include "status.h"

class Bench
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  Bench() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  Bench(const Bench&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default copy assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  Bench& operator=(const Bench&) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for constructing a Bench
  /// @param _slots index 0 for the active pokemon, 1-5 for the benched pokemon
  //----------------------------------------------------------------------------------------------------------------------
  Bench (const std::array<BoardSlot,6>& _slots):
    m_slots(_slots)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor for Bench
  //----------------------------------------------------------------------------------------------------------------------
  ~Bench() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returning the current status of the active pokemon in slot 0
  /// @return mutable pointer to the active pokemons status object
  //----------------------------------------------------------------------------------------------------------------------
  Status *activeStatus();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns a bench slot of the specified index
  /// @return pointer to the specified BenchSlot
  //----------------------------------------------------------------------------------------------------------------------
  BoardSlot *slotAt(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current active pokemon on this bench (0th slot), equivalent to slotAt(0)->active()
  /// @return the active pokemon of this bench, 0th index
  //----------------------------------------------------------------------------------------------------------------------
  PokemonCard *active();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return a clone of the entire bench for viewing
  /// @return a copy of the slots in this bench
  //----------------------------------------------------------------------------------------------------------------------
  std::array<BoardSlot,6> view() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief swapping bench slots when switching pokemon
  /// @param [in] _sub the replacement slot for the new active pokemon
  //----------------------------------------------------------------------------------------------------------------------
  void switchActive(const size_t &_sub);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief puts a card into the bench with a specified bench index
  /// @param [in] _card card to be put into slot
  /// @param [in] _index where the card is to be attached into the bench
  //----------------------------------------------------------------------------------------------------------------------
  void put(std::unique_ptr<Card> &&_card, const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief takes all cards from the slot at _index
  /// @param _index index of the slot in bench to take from
  /// @return a vector of cards that were on the slot
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> take(const size_t _index);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the number of occupied slots in the bench
  /// @return number of benched pokemon on this bench
  //----------------------------------------------------------------------------------------------------------------------
  unsigned numBenched() const;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief status handler for the active pokemon for this bench
  //----------------------------------------------------------------------------------------------------------------------
  Status m_activeStatus;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief slots in this bench
  //----------------------------------------------------------------------------------------------------------------------
  std::array<BoardSlot,6> m_slots;
};

#endif // BENCH_H
