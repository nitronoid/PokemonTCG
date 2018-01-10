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

//    Selector* hello = new Selector;
//    hello->addChild(new Action);

//    while(!hello->execute())
//        std::cout<<"STOP"<<'\n';
  // Simple test
  Game test;
  CardFactory testPool("../../Cards/SM/SUM/", "../PythonBindings/");
  testPool.init();

  SimplePrinter drawer;
  HumanPlayer a(test), b(test);
  test.init(testPool, &drawer, &a, &b);
  std::cout<<"BEGIN\n";
  //  std::unique_ptr<PokemonCard> foo(static_cast<PokemonCard*>(testPool.loadCard(53)));
  //  foo->attack(1, test);

  //  std::unique_ptr<TrainerCard> goo(static_cast<TrainerCard*>(testPool.loadCard(122)));
  //  goo->activateAbility(test);

  test.start();



  return 0;
}
