#ifndef BOARDSLOT_H
#define BOARDSLOT_H

#include "pokemoncard.h"
#include <unordered_set>
#include "energycard.h"
#include "trainercard.h"
#include <memory>
#include <unordered_set>


class BoardSlot
{
  using TypeMSet = std::unordered_multiset<PTCG::TYPE>;
public:
  /// @brief default ctor
  BoardSlot() = default;
  /// @brief default copy ctor
  BoardSlot(const BoardSlot &_original);
  /// @brief default move ctor
  BoardSlot (BoardSlot &&_origin) = default;
  /// @brief default assignment operator for copy ctor
  BoardSlot& operator=(const BoardSlot &_original);
  /// @brief default assignment operator for move ctor
  BoardSlot& operator=(BoardSlot &&_original) = default;

  /// @brief returns the turn this active pokemon has been played on this slot
  inline unsigned getTurnPlayed() const { return m_turnPlayed; }
  /// @brief return damage taken by the slotted pokemon on this bench
  inline int      getDamage()     const { return m_damageTaken; }
  /// @brief return slotted pokemon's Max HP - damage taken
  inline int      getRemainingHP()const { return std::max(0, active()->hp() - m_damageTaken);}
  /// @brief the pokemon on this slot takes damage
  /// @param [in] _damage damage this pokemon is about to take
  void takeDamage(const int _damage);
  /// @brief removing damage taken by the pokemon
  /// /// @param [in] _damage damage this pokemon is about to remove
  void removeDamage(const int _damage);
  /// @brief set pokemon's damage taken
  /// @param [in] _value value of damageTaken to set
  void setDamage(const int _value);
  /// @brief check if the pokemon is defeated
  bool isDefeated();
  /// @brief sets the turn that the slotted pokemon is played
  /// @param [in] _turn turn number to set the turn played
  void setTurnPlayed(const unsigned &_turn);
  /// @brief attaching a card to this slot
  /// @param [in] _card the card to be attached
  void attachCard(std::unique_ptr<Card> &&_card);
  /// @brief detach all pokemon card from this slot
  std::vector<std::unique_ptr<PokemonCard>> detachPokemon();
  /// @brief devolving this slotted pokemon, checking rulings
  std::unique_ptr<PokemonCard> devolvePokemon();
  /// @brief detach multiple energy cards from this slot
  std::vector<std::unique_ptr<EnergyCard>> detachEnergy();
  /// @brief discarding a single energy from this slot
  std::unique_ptr<EnergyCard> detachEnergy(const size_t _index);
  /// @brief detach a tool card from this slot
  std::unique_ptr<TrainerCard> detachTool();
  /// @brief attach one pokemon card to this slot
  /// @param [in] _pokemon pokemon card to be attached
  void setPokemon(std::unique_ptr<PokemonCard> &&_pokemon);
  /// @brief return the top pokemon card on this slot
  PokemonCard* active() const;
  /// @brief returns the set of attached energy cards
  TypeMSet energy() const;
  /// @brief returns number of pokemon cards in this slot
  inline size_t numPokemon() const { return m_pokemon.size(); }
  /// @brief returns number of energy cards in this slot
  inline size_t numEnergy() const { return m_energy.size(); }
  /// @brief returns number of tool cards in this slot
  inline size_t numTool() const { return m_tool ? 1 : 0; }
  /// @brief returns total number of cards in this slot
  inline size_t numCards() const { return numPokemon() + numEnergy() + numTool(); }
  /// @brief check if the current pokemon can evolve from an incoming pokemon card
  /// @param [in] _pokemon the pokemon to check against the evolution conditions
  bool canEvolve(PokemonCard * const _card, const unsigned &_turn);
  /// @brief viewing all energy cards in this slot
  std::vector<std::unique_ptr<Card>> viewEnergy();
  /// @brief view the tool card(s) in this slot
  std::unique_ptr<Card> viewTool();
  /// @brief swapping slot from an incoming slot
  /// @param [in] _slot the income slot to take this slot's index space
  void swap(BoardSlot& _slot);
private:

  /// @brief tool(s) attached to the slotted pokemon
  std::unique_ptr<TrainerCard> m_tool;
  /// @brief turn that the latest slotted pokemon is played
  unsigned m_turnPlayed = 0;
  /// @brief energy cards attached to the slotted pokemon
  std::vector<std::unique_ptr<EnergyCard>> m_energy;
  /// @brief all pokemon attached to this slot
  std::vector<std::unique_ptr<PokemonCard>> m_pokemon;
  /// @brief damage taken by the slotted pokemon
  int m_damageTaken = 0;
};

#endif // BOARDSLOT_H
