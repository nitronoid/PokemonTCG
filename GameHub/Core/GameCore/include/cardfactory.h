#ifndef CARDPOOL_H
#define CARDPOOL_H

#include "pokemoncard.h"
#include "trainercard.h"
#include "energycard.h"
#include <QJsonObject>
#include <memory>

class CardFactory
{
public:
  CardFactory(const std::string &_cardPath, const std::string &_pyLibPath) :
    m_cardPath(_cardPath),
    m_pyLibPath(_pyLibPath)
  {}

  void init();
  std::vector<std::unique_ptr<Card>> loadDeck(const std::string &_path) const;
  Card* loadCard(const unsigned _id) const;

private:
  PokemonCard* loadPokemonCard(const QJsonObject &_jsonCard) const;
  TrainerCard* loadTrainerCard(const QJsonObject &_jsonCard) const;
  EnergyCard*  loadEnergyCard (const QJsonObject &_jsonCard) const;

  const std::string m_cardPath;
  const std::string m_pyLibPath;
};

#endif // CARDPOOL_H
