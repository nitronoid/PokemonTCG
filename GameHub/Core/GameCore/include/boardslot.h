#ifndef BOARDSLOT_H
#define BOARDSLOT_H

#include "pokemoncard.h"
#include <unordered_set>
#include "energycard.h"
#include "trainercard.h"
#include <memory>

class BoardSlot
{
public:
    BoardSlot() = default;
    void setDamage(const int _value);
    void addCondition(const PTCG::CONDITION _condition);
    void removeCondition(const PTCG::CONDITION _condition);
    void removeAllConditions();
    void attachCard(std::unique_ptr<Card> &&_card);
    std::unique_ptr<Card> detachPokemon();
    std::unique_ptr<Card> detachEnergy(const unsigned _index);
    std::unique_ptr<Card> detachTool();
    void setPokemon(PokemonCard* const _pokemon);
private:
    std::unique_ptr<PokemonCard> m_pokemon;
    int m_damage;
    std::unordered_set<PTCG::CONDITION> m_conditions;
    std::vector<std::unique_ptr<EnergyCard>> m_energy;
    std::unique_ptr<TrainerCard> m_tool;
    std::vector<std::unique_ptr<PokemonCard>> m_basePokemons;
    const unsigned m_turnPlayed;
};

#endif // BOARDSLOT_H
