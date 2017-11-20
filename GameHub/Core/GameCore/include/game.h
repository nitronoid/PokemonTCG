#ifndef HUB_H
#define HUB_H

#include <iostream>
#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/embed.h>
#include "pokemoncard.h"

class Game
{
private:
  PTCG::TYPE selectType(const char &_energy);

public:
  // Temporarily public for testing!
  PokemonCard getCard(const unsigned id);

  void dealDamage(const int _damage);

};

#endif // HUB_H
