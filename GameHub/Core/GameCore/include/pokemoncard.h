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
  virtual bool canPlay() const override;

  virtual Card* clone() override;

  void attack(const unsigned &_attackIndex, Game& _game);

  virtual PTCG::CARD cardType()     const override;
  std::string preEvolution() const;
  PTCG::TYPE  type()         const;
  PTCG::TYPE  weakness()     const;
  PTCG::TYPE  resistance()   const;
  int         hp()           const;
  unsigned    retreatCost()  const;
  unsigned    stage()        const;

  const std::vector<Attack>& attacks() const;
  // Purely for testing
  unsigned    attackNum()    const;

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
