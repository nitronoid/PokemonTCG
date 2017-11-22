#include <iostream>
#include <memory>
#include <typeinfo>
#include <pybind11/embed.h>
#include "game.h"
#include "cardfactory.h"

// Needed for python attack functions
pybind11::scoped_interpreter m_python;

int main()
{
  // Simple test
  Game test;
  CardFactory testPool("../../Cards/SM/SUM/", "../PythonBindings/");
  testPool.init();
  std::unique_ptr<PokemonCard> foo(static_cast<PokemonCard*>(testPool.loadCard(9)));
  foo->attack("Tackle", test);
  return 0;
}
