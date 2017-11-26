#ifndef POKEMONCARD_H
#define POKEMONCARD_H

#include "card.h"
#include <vector>
#include <unordered_map>

class PokemonCard : public Card
{
public:
  PokemonCard(const PokemonCard&) = default;
  PokemonCard& operator=(const PokemonCard&) = delete;
  PokemonCard(
      const unsigned _id,
      const std::string &_name,
      const Ability & _ability,
      std::unordered_map<std::string, AttackFunc> && _attacks,
      std::unordered_map<std::string, std::vector<PTCG::TYPE>> && _costs,
      const PTCG::TYPE _type,
      const PTCG::TYPE _weakness,
      const PTCG::TYPE _resistance,
      const int _hp,
      const unsigned _retreatCost,
      const unsigned _stage
      ) :

    Card(_id, _name, _ability),
    m_attacks(_attacks),
    m_attackCost(_costs),
    m_type(_type),
    m_weakness(_weakness),
    m_resistance(_resistance),
    m_hp(_hp),
    m_retreatCost(_retreatCost),
    m_stage(_stage)
  {}

  virtual Card* clone() override
  {
    return new PokemonCard(*this);
  }

  inline void attack(const std::string &_attackName, const Game& _game)
  {
    m_attacks[_attackName](_game);
  }

  inline unsigned retreatCost() { return m_retreatCost; }

private:
  std::unordered_map<std::string, AttackFunc>              m_attacks;
  std::unordered_map<std::string, std::vector<PTCG::TYPE>> m_attackCost;
  const std::string m_preEvolution;
  const PTCG::TYPE  m_type;
  const PTCG::TYPE  m_weakness;
  const PTCG::TYPE  m_resistance;
  const int         m_hp;
  const unsigned    m_retreatCost;
  const unsigned    m_stage;

};

#endif // POKEMONCARD_H
