#include "pokemoncard.h"

bool PokemonCard::canPlay(Game &) const { return true; }

Card* PokemonCard::clone()
{
  return new PokemonCard(*this);
}

void PokemonCard::attack(const unsigned &_attackIndex, Game& _game)
{
  m_attacks[_attackIndex].attack(_game);
}

PTCG::CARD  PokemonCard::cardType()     const { return PTCG::CARD::POKEMON; }
std::string PokemonCard::preEvolution() const { return m_preEvolution; }
PTCG::TYPE  PokemonCard::type()         const { return m_type; }
PTCG::TYPE  PokemonCard::weakness()     const { return m_weakness; }
PTCG::TYPE  PokemonCard::resistance()   const { return m_resistance; }
int         PokemonCard::hp()           const { return m_hp; }
unsigned    PokemonCard::retreatCost()  const { return m_retreatCost; }
unsigned    PokemonCard::stage()        const { return m_stage; }

const std::vector<Attack>& PokemonCard::attacks() const { return m_attacks; }

unsigned PokemonCard::attackNum() const { return static_cast<unsigned>(m_attacks.size()); }
