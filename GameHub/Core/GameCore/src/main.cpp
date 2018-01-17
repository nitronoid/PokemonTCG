#include <iostream>
#include <memory>
#include <typeinfo>
#include "game.h"
#include "gui/simpleprinter.h"
#include "gamelogger.h"
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
  // Logger and ascii-gui
  GameLogger logger;
  SimplePrinter drawer;
  // Two players for the game
  HumanPlayer firstPlayer(&game);
  RandomAI secondPlayer(&game);
  // Load the decks from the pool and attach players
  game.init(sumFactory, &firstPlayer, &secondPlayer);
  // Attach both the log and the gui
  game.registerObserver(&drawer);
  game.registerObserver(&logger);
  // Play the game
  game.playGame();
  return EXIT_SUCCESS;
}
