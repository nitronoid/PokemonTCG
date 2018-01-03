#include "cardfactory.h"
#include "game.h"
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <QJsonArray>

void CardFactory::init()
{
  // Append directories for card functions and python bindings
  auto sys = pybind11::module::import("sys");
  sys.attr("path").attr("append")(m_pyLibPath);
  sys.attr("path").attr("append")(m_cardPath);
}

void getJsonDoc(QJsonObject* io_jsonCard, const std::string &_path)
{
  QFile file(QString::fromStdString(_path));
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QByteArray rawData = file.readAll();
  // Parse document
  QJsonDocument doc(QJsonDocument::fromJson(rawData));
  // Get JSON object
  *io_jsonCard = doc.object();
}

std::string stringify(const QJsonValue _jStr)
{
  return _jStr.toString().toStdString();
}

int intify(const QJsonValue _jStr)
{
  return _jStr.toInt();
}

std::vector<std::unique_ptr<Card>> CardFactory::loadDeck(const std::string &_path) const
{
  std::vector<std::unique_ptr<Card>> deck;
  QJsonObject jDeck;
  getJsonDoc(&jDeck, m_cardPath + _path);
  for (const auto cardID : jDeck["Deck"].toArray())
  {
    deck.emplace_back(loadCard(intify(cardID)));
  }
  return deck;
}

PTCG::TYPE selectType(const char _energy)
{
  switch (_energy)
  {
    case 'C':  return PTCG::TYPE::COLOURLESS;
    case 'F':  return PTCG::TYPE::FIGHTING;
    case 'L':  return PTCG::TYPE::LIGHTNING;
    case 'G':  return PTCG::TYPE::GRASS;
    case 'P':  return PTCG::TYPE::PSYCHIC;
    case 'M':  return PTCG::TYPE::METAL;
    case 'W':  return PTCG::TYPE::WATER;
    case 'D':  return PTCG::TYPE::DARKNESS;
    case 'R':  return PTCG::TYPE::FIRE;
    case 'N':  return PTCG::TYPE::DRAGON;
    case 'Y':  return PTCG::TYPE::FAIRY;

    default: return PTCG::TYPE::ERROR;
  }
}

std::vector<PTCG::TYPE> getEnergyList(const std::string _energyString)
{
  std::vector<PTCG::TYPE> energyList;
  energyList.reserve(_energyString.size());
  for (const auto& c : _energyString)
  {
    energyList.push_back(selectType(c));
  }
  return energyList;
}

PTCG::DURATION selectDuration(const char _c)
{
  switch (_c)
  {
    case 'S':  return PTCG::DURATION::SINGLE;
    case 'M':  return PTCG::DURATION::MULTIPLE;
    case 'P':  return PTCG::DURATION::PERMANENT;
    default:   return PTCG::DURATION::SINGLE;
  }
}

PTCG::TRIGGER selectPhase(const char _c)
{
  switch (_c)
  {
    case 'N':  return PTCG::TRIGGER::NOW;
    case 'A':  return PTCG::TRIGGER::ATTACK;
    case 'E':  return PTCG::TRIGGER::END;
    default:   return PTCG::TRIGGER::NONE;
  }
}

PTCG::CARD selectTrainerType(const char _c)
{
  switch (_c)
  {
    case 'I':  return PTCG::CARD::ITEM;
    case 'T':  return PTCG::CARD::TOOL;
    case 'S':  return PTCG::CARD::SUPPORT;
    case 'A':  return PTCG::CARD::STADIUM;
    default:   return PTCG::CARD::SUPPORT;
  }
}


Ability loadAbility(const QJsonObject  &_jsonCard)
{
  Ability cardAbility;
  int id = intify(_jsonCard["ID"]);
  // Import this cards attacks
  try
  {
    auto module = pybind11::module::import(std::to_string(id).c_str());

    if (_jsonCard.contains("Ability"))
    {
      auto jAbility = _jsonCard["Ability"].toObject();
      auto pyfunc = module.attr(stringify(jAbility["func"]).c_str());
      auto ability = pyfunc.cast<AbilityFunc>();
      cardAbility = Ability(ability, selectPhase(stringify(jAbility["phase"])[0]), selectDuration(stringify(jAbility["duration"])[0]));
    }
  }
  catch (pybind11::error_already_set e)
  {
    std::cerr<<"No python module was found for card "<<id<<'\n'<<e.what()<<'\n';
  }
  return cardAbility;
}

PokemonCard* CardFactory::loadPokemonCard(const QJsonObject  &_jsonCard) const
{
  // Import this cards attacks
  auto module = pybind11::module::import(std::to_string(intify(_jsonCard["ID"])).c_str());

  // Add each attack to the map
  std::vector<Attack> attacks;
  auto jAttackObj = _jsonCard["Attacks"].toObject();
  auto names = jAttackObj.keys();
  attacks.reserve(static_cast<size_t>(names.size()));
  for(const auto& attackName : names)
  {
    // Load the attack
    auto attackObj = jAttackObj[attackName].toObject();
    auto pyfunc = module.attr(stringify(attackObj["func"]).c_str());
    Attack newAttack(pyfunc.cast<AttackFunc>(),
                     attackName.toStdString(),
                     getEnergyList(stringify(attackObj["energy"])));
    attacks.push_back(newAttack);
  }

  return new PokemonCard(
      static_cast<unsigned>(intify(_jsonCard["ID"])),
      stringify(_jsonCard["Name"]),
      loadAbility(_jsonCard),
      std::move(attacks),
      selectType(stringify(_jsonCard["Type"])[0]),
      selectType(stringify(_jsonCard["Weakness"])[0]),
      selectType(stringify(_jsonCard["Resistance"])[0]),
      intify(_jsonCard["HP"]),
      static_cast<unsigned>(intify(_jsonCard["Retreat"])),
      static_cast<unsigned>(intify(_jsonCard["Stage"]))
      );
}

TrainerCard* CardFactory::loadTrainerCard(const QJsonObject &_jsonCard) const
{
  // Import this cards ability
  return new TrainerCard(
        static_cast<unsigned>(intify(_jsonCard["ID"])),
        stringify(_jsonCard["Name"]),
        loadAbility(_jsonCard),
        selectTrainerType(stringify(_jsonCard["Trainer"])[0])
        );
}

EnergyCard*  CardFactory::loadEnergyCard(const QJsonObject &_jsonCard) const
{
  // Import this cards ability
  return new EnergyCard(
        static_cast<unsigned>(intify(_jsonCard["ID"])),
        stringify(_jsonCard["Name"]),
        loadAbility(_jsonCard),
        static_cast<unsigned>(intify(_jsonCard["Ammount"])),
        selectType(stringify(_jsonCard["Type"])[0])
        );
}

Card* CardFactory::loadCard(const unsigned _id) const
{
  // Load the json card
  QJsonObject jsonCard;
  getJsonDoc(&jsonCard, m_cardPath + std::to_string(_id) + ".json");
  if (jsonCard.contains("HP"))
  {
    return loadPokemonCard(jsonCard);
  }
  else if (jsonCard.contains("Trainer"))
  {
    return loadTrainerCard(jsonCard);
  }
  else if (jsonCard.contains("Type"))
  {
    return  loadEnergyCard(jsonCard);
  }
  return nullptr;
}






