#include <iostream>
#include <memory>
#include <typeinfo>
#include <pybind11/embed.h>
#include "game.h"
#include "simpleprinter.h"
#include "cardfactory.h"

// Needed for python attack functions
pybind11::scoped_interpreter m_python;

int main()
{
  // Simple test
  Game test;
  CardFactory testPool("../../Cards/SM/SUM/", "../PythonBindings/");
  testPool.init();
//  std::unique_ptr<PokemonCard> foo(static_cast<PokemonCard*>(testPool.loadCard(103)));
//  foo->attack(0, test);

//  std::unique_ptr<TrainerCard> goo(static_cast<TrainerCard*>(testPool.loadCard(122)));
//  goo->activateAbility(test);


  SimplePrinter drawer;
  test.init(testPool, &drawer, "test_deck.json", "test_deck.json");
  test.start();

  return 0;
}
