#include "cardpool.h"
#include "game.h"
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

void CardPool::init()
{
  // Append directories for card functions and python bindings
  auto sys = pybind11::module::import("sys");
  sys.attr("path").attr("append")(m_pyLibPath);
  sys.attr("path").attr("append")(m_cardPath);
}

std::vector<PTCG::TYPE> CardPool::getEnergyList(const std::string _energyString) const
{
  std::vector<PTCG::TYPE> energyList;
  for (const auto& c : _energyString)
  {
    energyList.push_back(selectType(c));
  }
  return energyList;
}

PTCG::TYPE CardPool::selectType(const char &_energy) const
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

PokemonCard CardPool::loadPokemonCard(const unsigned _id) const
{
  // Helpers
  auto stringify = [](auto jStr) { return jStr.toString().toStdString(); };
  auto intify = [](auto jStr) { return jStr.toInt(); };

  // Load the json card
  QJsonObject jsonCard;
  getJsonCard(&jsonCard, m_cardPath + std::to_string(_id) + ".json");

  // Import this cards attacks
  auto module = pybind11::module::import(std::to_string(_id).c_str());

  // Add each attack to the map
  std::unordered_map<std::string, AttackFunc> attacks;
  std::unordered_map<std::string, std::vector<PTCG::TYPE>> attackCosts;
  auto jAttackObj = jsonCard["Attacks"].toObject();
  for(const auto& attackName : jAttackObj.keys())
  {
    // Load the attack
    auto attackObj = jAttackObj[attackName].toObject();
    auto pyfunc = module.attr(stringify(attackObj["func"]).c_str());
    attacks[attackName.toStdString()] = pyfunc.cast<std::function<void(const Game&)>>();
    attackCosts[attackName.toStdString()] = getEnergyList(stringify(attackObj["energy"]));
  }

  return PokemonCard(
      intify(jsonCard["ID"]),
      stringify(jsonCard["Name"]),
      Ability(),
      std::move(attacks),
      std::move(attackCosts),
      selectType(stringify(jsonCard["Type"])[0]),
      selectType(stringify(jsonCard["Weakness"])[0]),
      selectType(stringify(jsonCard["Resistance"])[0]),
      intify(jsonCard["HP"]),
      intify(jsonCard["Retreat"]),
      intify(jsonCard["Stage"])
      );
}

