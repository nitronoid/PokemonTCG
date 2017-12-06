#ifndef BOARDSLOT_H
#define BOARDSLOT_H

#include "pokemoncard.h"
#include <unordered_set>
#include "energycard.h"
#include "trainercard.h"
#include <memory>
#include <stack>
#include <unordered_set>


class BoardSlot
{
using TypeMSet = std::unordered_multiset<PTCG::TYPE>;
public:
    BoardSlot() = default;
    BoardSlot(const BoardSlot &_original);
    BoardSlot& operator=(const BoardSlot &_original) = delete;

    void setDamage(const int _value);
    void addCondition(const PTCG::CONDITION _condition);
    void removeCondition(const PTCG::CONDITION _condition);
    void removeAllConditions();
    void attachCard(std::unique_ptr<Card> &&_card);
    std::vector<std::unique_ptr<PokemonCard>> detachPokemon();
    std::unique_ptr<PokemonCard> devolvePokemon();
    std::vector<std::unique_ptr<EnergyCard>> detachEnergy();
    std::unique_ptr<EnergyCard> detachEnergy(const unsigned _index);
    std::unique_ptr<TrainerCard> detachTool();
    void setPokemon(std::unique_ptr<PokemonCard> &&_pokemon);
    PokemonCard* active() const;
    TypeMSet energy() const;
private:
    std::unordered_set<PTCG::CONDITION> m_conditions;
    std::unique_ptr<TrainerCard> m_tool;
    int m_damage = 0;
    unsigned m_turnPlayed = 0;
    std::vector<std::unique_ptr<EnergyCard>> m_energy;
    std::vector<std::unique_ptr<PokemonCard>> m_pokemon;

};

#endif // BOARDSLOT_H
