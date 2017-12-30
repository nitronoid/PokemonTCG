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
    BoardSlot() = default;
    BoardSlot(const BoardSlot &_original);
    BoardSlot (BoardSlot &&_origin) = default;
    BoardSlot& operator=(const BoardSlot &_original);

    inline int getDamage() const {return m_damageTaken;}
    inline int getBonusBefore() const {return m_bonusDamageBefore;}
    inline int getBonusAfter() const {return m_bonusDamageAfter;}
    inline int getReductionBefore() const {return m_damageReductionBefore;}
    inline int getReductionAfter() const {return m_damageReductionAfter;}
    inline unsigned getTurnPlayed() const {return m_turnPlayed;}

    void takeDamage(const int _damage);
    void setDamage(const int _value);
    void addCondition(const PTCG::CONDITION _condition);
    void removeCondition(const PTCG::CONDITION _condition);
    void removeAllConditions();
    bool isDefeated();

    void attachCard(std::unique_ptr<Card> &&_card);
    std::vector<std::unique_ptr<PokemonCard>> detachPokemon();
    std::unique_ptr<PokemonCard> devolvePokemon();
    std::vector<std::unique_ptr<EnergyCard>> detachEnergy();
    std::unique_ptr<EnergyCard> detachEnergy(const unsigned _index);
    std::unique_ptr<TrainerCard> detachTool();
    void setPokemon(std::unique_ptr<PokemonCard> &&_pokemon);
    PokemonCard* active() const;
    TypeMSet energy() const;
    std::vector<PTCG::CONDITION> conditions() const;

    inline size_t numPokemon() const { return m_pokemon.size(); }
    inline size_t numEnergy() const { return m_energy.size(); }
    inline size_t numTool() const { return m_tool ? 1 : 0; }
    inline size_t numCards() const { return numPokemon() + numEnergy() + numTool(); }
    bool canEvolve(const std::unique_ptr<PokemonCard> &_card, const unsigned &_turn);
    std::vector<std::unique_ptr<Card>> viewEnergy();
    std::unique_ptr<Card> viewTool();
private:
    std::unordered_set<PTCG::CONDITION> m_conditions;
    std::unique_ptr<TrainerCard> m_tool;
    int m_damageTaken = 0;
    int m_bonusDamageBefore = 0;
    int m_bonusDamageAfter = 0;
    int m_damageReductionBefore = 0;
    int m_damageReductionAfter = 0;
    unsigned m_turnPlayed = 0;
    std::vector<std::unique_ptr<EnergyCard>> m_energy;
    std::vector<std::unique_ptr<PokemonCard>> m_pokemon;

};

#endif // BOARDSLOT_H
