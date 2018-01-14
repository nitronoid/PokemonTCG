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
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for constructing a CardFactory
  /// @param [in] _cardPath path to reach card files for loading
  /// @param [in] _pyLibPath path to find pybind11 for binding python scripts with cpp codes
  //----------------------------------------------------------------------------------------------------------------------
  CardFactory(const std::string &_cardPath, const std::string &_pyLibPath) :
    m_cardPath(_cardPath),
    m_pyLibPath(_pyLibPath)
  {}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default dtor for CardFactory
  //----------------------------------------------------------------------------------------------------------------------
  ~CardFactory() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialises the CardFactory, call this after construction
  //----------------------------------------------------------------------------------------------------------------------
  void init();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief looking through a decklist file to load cards accordingly
  /// @param [in] _path path to reach decklist files
  /// @return the loaded cards for the deck
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<Card>> loadDeck(const std::string &_path) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief loading a specific card with a card ID
  /// @param [in] _id ID of the cards in a card set
  /// @return the loaded card requested
  //----------------------------------------------------------------------------------------------------------------------
  Card* loadCard(const unsigned _id) const;

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief for loading a Pokemon card (json and Python) and binding it with a PokemonCard object
  /// @param [in] _jsonCard QObject for loaded json files
  /// @return loaded pokemon card requested
  //----------------------------------------------------------------------------------------------------------------------
  PokemonCard* loadPokemonCard(const QJsonObject &_jsonCard) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief for loading a Trainercard (json and Python) and binding it with a PokemonCard object
  /// @param [in] _jsonCard QObject for loaded json files
  /// @return loaded trainer card requested
  //----------------------------------------------------------------------------------------------------------------------
  TrainerCard* loadTrainerCard(const QJsonObject &_jsonCard) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief for loading a Energycard (json and Python) and binding it with a PokemonCard object
  /// @param [in] _jsonCard QObject for loaded json files
  /// @return loaded energy card requested
  //----------------------------------------------------------------------------------------------------------------------
  EnergyCard*  loadEnergyCard (const QJsonObject &_jsonCard) const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief path to reach card files for loading
  //----------------------------------------------------------------------------------------------------------------------
  const std::string m_cardPath;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief path to find pybind11 for binding python scripts with cpp codes
  //----------------------------------------------------------------------------------------------------------------------
  const std::string m_pyLibPath;
};

#endif // CARDPOOL_H
