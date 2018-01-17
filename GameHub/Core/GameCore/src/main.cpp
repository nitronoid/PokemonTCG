#include <iostream>
#include <memory>
#include <typeinfo>
#include <pybind11/embed.h>
#include "game.h"
#include "simpleprinter.h"
#include "gamelogger.h"
#include "cardfactory.h"
#include "randomai.h"
#include "RoaringFluke.h"


int main()
{
  // Needed for python attack functions
  pybind11::scoped_interpreter m_python;

  // Simple test
  Game test;
  CardFactory testPool("../../Cards/SM/SUM/", "../PythonBindings/");
  testPool.init();

  GameLogger logger;
  SimplePrinter drawer;
  RoaringFluke a(&test);
  RandomAI b(&test);
  test.init(testPool, &a, &b);
  test.registerObserver(&drawer);
  test.registerObserver(&logger);
  std::cout<<"BEGIN\n";
  //  std::unique_ptr<PokemonCard> foo(static_cast<PokemonCard*>(testPool.loadCard(53)));
  //  foo->attack(1, test);

  //  std::unique_ptr<TrainerCard> goo(static_cast<TrainerCard*>(testPool.loadCard(122)));
  //  goo->activateAbility(test);

  test.playGame();

  return 0;
}
