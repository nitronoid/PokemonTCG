#include <iostream>
#include <memory>
#include <typeinfo>
#include <pybind11/embed.h>
#include "game.h"
#include "cardpool.h"

// Needed for python attack functions
pybind11::scoped_interpreter m_python;

int main()
{
  // Simple test
  Game test;
  CardPool testPool("../../Cards/SM/SUM/", "../PythonBindings/");
  testPool.init();
  PokemonCard foo = testPool.loadPokemonCard(9);
  foo.attack("Tackle",test);
  return 0;
}
