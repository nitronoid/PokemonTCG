#ifndef CARDPOOL_H
#define CARDPOOL_H

#include "pokemoncard.h"

class CardPool
{
public:
  CardPool(const std::string &_cardPath, const std::string &_pyLibPath) :
    m_cardPath(_cardPath),
    m_pyLibPath(_pyLibPath)
  {}
  void init();
  // Temporarily public for testing!
  PokemonCard loadPokemonCard(const unsigned _id) const;
private:
  PTCG::TYPE selectType(const char &_energy) const;
  std::vector<PTCG::TYPE> getEnergyList(const std::string _energyString) const;

  const std::string m_cardPath;
  const std::string m_pyLibPath;
};

#endif // CARDPOOL_H
