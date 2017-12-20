#ifndef POKEMONCARD_H
#define POKEMONCARD_H

#include "card.h"
#include "attack.h"
#include <vector>

class PokemonCard : public Card
{
public:
  PokemonCard(const PokemonCard&) = default;
  PokemonCard& operator=(const PokemonCard&) = delete;
  PokemonCard(
      const unsigned _id,
      const std::string &_name,
      const Ability & _ability,
      std::vector<Attack> && _attacks,
      const PTCG::TYPE _type,
      const PTCG::TYPE _weakness,
      const PTCG::TYPE _resistance,
      const int _hp,
      const unsigned _retreatCost,
      const unsigned _stage
      ) :

    Card(_id, _name, _ability),
    m_type(_type),
    m_weakness(_weakness),
    m_resistance(_resistance),
    m_attacks(_attacks),
    m_hp(_hp),
    m_retreatCost(_retreatCost),
    m_stage(_stage)
  {}

  // Fix this later
  virtual bool canPlay() override { return true; }

  virtual Card* clone() override
  {
    return new PokemonCard(*this);
  }

  inline void attack(const unsigned &_attackIndex, Game& _game)
  {
    m_attacks[_attackIndex].attack(_game);
  }

  virtual PTCG::CARD cardType()     const override { return PTCG::CARD::POKEMON; }
  inline std::string preEvolution() const { return m_preEvolution; }
  inline PTCG::TYPE  type()         const { return m_type; }
  inline PTCG::TYPE  weakness()     const { return m_weakness; }
  inline PTCG::TYPE  resistance()   const { return m_resistance; }
  inline int         hp()           const { return m_hp; }
  inline unsigned    retreatCost()  const { return m_retreatCost; }
  inline unsigned    stage()        const { return m_stage; }

  // Purely for testing
  inline unsigned    attackNum()    const { return m_attacks.size(); }

private:
  PTCG::TYPE  m_type;
  PTCG::TYPE  m_weakness;
  PTCG::TYPE  m_resistance;
  std::vector<Attack> m_attacks;
  std::string m_preEvolution;  //ADD TO CONSTRUCTOR
  int         m_hp;
  unsigned    m_retreatCost;
  unsigned    m_stage;

};

#endif // POKEMONCARD_H
