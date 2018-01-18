#include <iostream>
#include <memory>
#include <typeinfo>
#include "game.h"
#include "observers/simpleprinter.h"
#include "observers/gamelogger.h"
#include "observers/gamestaller.h"
#include "card/cardfactory.h"
#include "player/randomai.h"
#include "player/humanplayer.h"
#include "RoaringFluke.h"



int main()
{
  // Create a game
  Game game;
  // Set up a factory for this card set, needs the directory to the cards and to the python bindings
  CardFactory sumFactory("../../Cards/SM/SUM/", "../PythonBindings/");
  sumFactory.init();
  //Logger, ascii-gui and a staller so we can watch AI play
  //GameLogger logger;
  SimplePrinter drawer;
  GameStaller staller(0);
  // Two players for the game
  //RandomAI firstPlayer(&game);
  HumanPlayer firstPlayer(&game);
  RandomAI secondPlayer(&game);
  // Load the decks from the pool and attach players
  game.init(sumFactory, &firstPlayer, &secondPlayer);
  // Attach our observers
  //game.registerObserver(&logger);
  game.registerObserver(&staller);
  game.registerObserver(&drawer);
  // Play the game
  game.playGame();
  return EXIT_SUCCESS;

}
