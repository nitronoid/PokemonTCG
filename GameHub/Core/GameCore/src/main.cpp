#include <iostream>
#include <memory>
#include <typeinfo>
#include "game.h"

// Needed for python attack functions
pybind11::scoped_interpreter m_python;

int main()
{
  // Simple test
  Game test;
  PokemonCard foo = test.getCard(9);
  foo.attack(1,test);
  return 0;
}
