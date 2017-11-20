#include "game.h"


PTCG::TYPE Game::selectType(const char &_energy)
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

PokemonCard Game::getCard(const unsigned id)
{
  // Helpers
  auto stringify = [](auto jStr) { return jStr.toString().toStdString(); };
  auto intify = [](auto jStr) { return jStr.toInt(); };

  // Paths to cards and bindings
  constexpr auto cardPath = "../../Cards/SM/SUM/";
  constexpr auto pylibPath = "../PythonBindings/";

  QFile file(QString(cardPath) + QString::number(id) + ".json");
  file.open(QIODevice::ReadOnly);
  QByteArray rawData = file.readAll();
  // Parse document
  QJsonDocument doc(QJsonDocument::fromJson(rawData));
  // Get JSON object
  QJsonObject jsonCard = doc.object();
  PokemonCard ret(intify(jsonCard["ID"]), intify(jsonCard["HP"]), stringify(jsonCard["Name"]), selectType(stringify(jsonCard["Type"])[0]));

  // Append directories for card functions and python bindings
  auto sys = pybind11::module::import("sys");
  sys.attr("path").attr("append")(pylibPath);
  sys.attr("path").attr("append")(cardPath);

  // Import this cards attacks
  auto module = pybind11::module::import(std::to_string(id).c_str());
  // Add each attack to the array
  for(const auto& jAttack : jsonCard["Attacks"].toObject())
  {
    // Load the attack
    auto attackObj = jAttack.toObject();
    auto pyfunc = module.attr(stringify(attackObj["func"]).c_str());
    ret.addAttack(pyfunc.cast<std::function<void(const Game&)>>());
  }

  return ret;
}

void Game::dealDamage(const int _damage)
{
  std::cout<<"Attack did: "<<_damage<<" damage!\n";
}

