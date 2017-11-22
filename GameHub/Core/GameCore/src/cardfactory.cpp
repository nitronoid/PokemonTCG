#include "cardfactory.h"
#include "game.h"
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

void CardFactory::init()
{
  // Append directories for card functions and python bindings
  auto sys = pybind11::module::import("sys");
  sys.attr("path").attr("append")(m_pyLibPath);
  sys.attr("path").attr("append")(m_cardPath);
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

    default: return PTCG::DURATION::SINGLE;
  }
}

PTCG::PHASE selectPhase(const char _c)
{
  switch (_c)
  {
    case 'D':  return PTCG::PHASE::DRAW;
    case 'M':  return PTCG::PHASE::MAIN;
    case 'A':  return PTCG::PHASE::ATTACK;

    default: return PTCG::PHASE::NONE;
  }
}

PTCG::TRAINER selectTrainerType(const char _c)
{
  switch (_c)
  {
    case 'I':  return PTCG::TRAINER::ITEM;
    case 'T':  return PTCG::TRAINER::TOOL;
    case 'S':  return PTCG::TRAINER::SUPPORT;
    case 'A':  return PTCG::TRAINER::STADIUM;

    default: return PTCG::TRAINER::SUPPORT;
  }
}

void getJsonCard(QJsonObject* io_jsonCard, const std::string &_path)
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

PokemonCard* CardFactory::loadPokemonCard(const QJsonObject  &_jsonCard) const
{
  // Import this cards attacks
  auto module = pybind11::module::import(std::to_string(intify(_jsonCard["ID"])).c_str());

  // Add each attack to the map
  std::unordered_map<std::string, AttackFunc> attacks;
  std::unordered_map<std::string, std::vector<PTCG::TYPE>> attackCosts;
  auto jAttackObj = _jsonCard["Attacks"].toObject();
  for(const auto& attackName : jAttackObj.keys())
  {
    // Load the attack
    auto attackObj = jAttackObj[attackName].toObject();
    auto pyfunc = module.attr(stringify(attackObj["func"]).c_str());
    attacks[attackName.toStdString()] = pyfunc.cast<AttackFunc>();
    attackCosts[attackName.toStdString()] = getEnergyList(stringify(attackObj["energy"]));
  }

  Ability cardAbility;
  if (_jsonCard.contains("Ability"))
  {
    auto jAbility = _jsonCard["Ability"].toObject();
    auto pyfunc = module.attr(stringify(jAbility["func"]).c_str());
    auto ability = pyfunc.cast<AbilityFunc>();
    cardAbility = Ability(ability, selectPhase(stringify(jAbility["phase"])[0]), selectDuration(stringify(jAbility["duration"])[0]));
  }

  return new PokemonCard(
      intify(_jsonCard["ID"]),
      stringify(_jsonCard["Name"]),
      cardAbility,
      std::move(attacks),
      std::move(attackCosts),
      selectType(stringify(_jsonCard["Type"])[0]),
      selectType(stringify(_jsonCard["Weakness"])[0]),
      selectType(stringify(_jsonCard["Resistance"])[0]),
      intify(_jsonCard["HP"]),
      intify(_jsonCard["Retreat"]),
      intify(_jsonCard["Stage"])
      );
}

TrainerCard* CardFactory::loadTrainerCard(const QJsonObject &_jsonCard) const
{
  // Import this cards attacks
  auto module = pybind11::module::import(std::to_string(intify(_jsonCard["ID"])).c_str());
  auto jAbility = _jsonCard["Ability"].toObject();
  auto pyfunc = module.attr(stringify(jAbility["func"]).c_str());
  auto ability = pyfunc.cast<AbilityFunc>();
  return new TrainerCard(
        intify(_jsonCard["ID"]),
        stringify(_jsonCard["Name"]),
        Ability(ability, selectPhase(stringify(jAbility["phase"])[0]), selectDuration(stringify(jAbility["duration"])[0])),
        selectTrainerType(stringify(_jsonCard["Type"])[0])
        );
}

Card* CardFactory::loadCard(const unsigned _id) const
{
  // Load the json card
  QJsonObject jsonCard;
  getJsonCard(&jsonCard, m_cardPath + std::to_string(_id) + ".json");
  if (jsonCard.contains("HP"))
  {
    return loadPokemonCard(jsonCard);
  }
  else if (jsonCard.contains("Ability"))
  {
    return loadTrainerCard(jsonCard);
  }
//  else if (jsonCard.contains("Type"))
//  {

//  }
  return nullptr;
}






